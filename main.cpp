#include <cstring>
#include <cassert>
#include <functional>
#include "crc32_test/headers/Config.h"

static const uint32_t mag = 0x6D616368;

enum Type {

    URL,
    PASSWORD,
    LOGIN
};

struct Field {

    char data[128];
    enum Type type;
    uint8_t size;

    Field *next = nullptr;
};

static Field fields_test[3]; // for tests

struct Record {

    uint16_t id;
    uint16_t pid;
    bool isDir;
    uint32_t lastUpdate;
    uint8_t count;
    uint8_t type;
    char name[128];

    Field *fields;
};

/// ConfigSectionDescriptor<Record> specialization.
template<>
struct ConfigSectionDescriptor<Record> {

    template<class Archive>
    static constexpr auto pack(Archive &&ar, Record &x) {

        return ar & x.id & x.pid & x.isDir & x.lastUpdate & x.count & x.type;
    }
};

const uint16_t db_size = 20; // Size of database
const uint16_t record_size = 1024; // Size of record
static char database[db_size][record_size]; // new serialized database

uint8_t normalizeLen(const char *str, uint8_t MaxAllowSizeOfData) {

    for (int i = 0; i <= MaxAllowSizeOfData; i++)
        if (str[i] == '\0')
            return i;

    return MaxAllowSizeOfData;
}

size_t findBlock(uint16_t id, char **pBlock) {

    size_t index_cnt = 0;

    for (auto &block : database) {

        Deserializer des(block, sizeof(uint32_t) + sizeof(uint16_t));
        uint16_t id_from_db = 0;
        uint32_t magic0 = 0;
        des.deserialize(&magic0);
        des.deserialize(&id_from_db);

        if (magic0 == mag and id_from_db == id) {

            (*pBlock) = block;
            return index_cnt;
        }

        index_cnt++;
    }

    for (auto &block : database) {

        Deserializer des(block, sizeof(uint32_t));
        uint32_t magic0 = 0;
        des.deserialize(&magic0);

        if (magic0 == 0) {

            (*pBlock) = block;
            return index_cnt;
        }

        index_cnt++;
    }

    return -1;
}

void reserve() { // TODO: lock the block in database
}

void release() { //TODO: unlock the block in database
}


class StateMachine {
public:

    void getHeader(Deserializer *des) {

        uint32_t mag0 = 0;
        des->deserialize(&mag0);

        if (mag == mag0) {

            memset(m_record->name, 0, 128);
            ConfigSectionDescriptor<Record>::pack(*des, *m_record);
            des->deserialize(m_record->name, 1);
        }

    }

    void getField(Deserializer *des, Field **tail) {

        memset((*tail)->data, 0, 128);
        des->deserialize((*tail)->data, 1);
    }

    bool begin(Record *newRecord) {

        if (not beginState)
            return false;

        index = findBlock(newRecord->id, &pBlock);

        if (index == -1) {
            return false;

        } else if (index >= 0) {
            reserve();

            m_record->id = newRecord->id;
            m_record->pid = newRecord->pid;
            m_record->isDir = newRecord->isDir;
            m_record->lastUpdate = newRecord->lastUpdate;
            m_record->type = newRecord->type;
            memset(m_record->name, 0, 128);
            uint16_t name_len = normalizeLen(newRecord->name, 127);
            strncpy(m_record->name, newRecord->name, name_len);
            m_record->count = newRecord->count;
        }

        beginState = false;
        return true;
    }

    bool setField(Field *newField) {

        assert(newField != nullptr);

        if (not m_record->isDir and not beginState) {

            auto *field0 = (Field *) malloc(sizeof(Field));
            if (m_lastField == nullptr) {

                m_record->fields = field0;
            }

            field0->type = newField->type;
            field0->size = normalizeLen(newField->data, 127);
            memset(field0->data, 0, 128);
            strncpy(field0->data, newField->data, field0->size);

            field0->next = nullptr;
            if (m_lastField)
                m_lastField->next = field0;

            m_lastField = field0;
            return true;
        }
        return false;
    }

    bool end(bool commit) {

        if (not m_record and not beginState)
            return false;

        if (commit) {

            Serializer ser(pBlock, record_size);
            ser.serialize(mag);
            ConfigSectionDescriptor<Record>::pack(ser, *m_record);
            ser.serialize(m_record->name);

            auto *tail = m_record->fields;
            int i = 0;
            while (i < m_record->count) {

                ser.serialize(tail->data, tail->size);
                tail = m_record->fields->next;
                i++;
            }

            release();
        }

        beginState = true;
        return true;
    }

    bool readRecord(uint16_t id) {

        index = findBlock(id, &pBlock);

        if (index == -1) {
            return false;

        } else if (index >= 0) {

            reserve();
            Deserializer des(pBlock, record_size);
            getHeader(&des);

            auto *tail = m_record->fields;
            int i = 0;
            while (i < m_record->count) {

                memset(tail->data, 0, 128);
                des.deserialize(tail->data, 1);
                tail = m_record->fields->next;
                i++;
            }
        }

        return true;
    }

    uint16_t createUpdateRecord(Record *newRecord) {

        if (newRecord == nullptr)
            return -1;

        if (begin(newRecord)) {

            auto *tail = newRecord->fields;

            for (int i = 0; i < newRecord->count; i++) {

                setField(tail);
                tail = tail->next;
            }

            m_lastField = nullptr;
            end(true);
        }

        return newRecord->id;
    }

    void deleteRecord(uint16_t id) {

        Deserializer des(pBlock, sizeof(uint32_t));
        Serializer ser(pBlock, sizeof(uint32_t));
        uint32_t mag0 = 0;

        des.deserialize(&mag0);
        mag0 = 0;
        ser.serialize(mag0);
    }

    ////////////// Only for tests ////////////

    Record *getRecord() { return m_record; }
    ////////////// Only for tests ////////////

private:
    struct Record record{};

    Record *m_record = &record;
    Field *m_lastField = nullptr;

    char *pBlock = nullptr;
    bool beginState = true;
    size_t index = 0;
    uint8_t count = 0;
};


/////////////////////////////////////////// Test methods ///////////////////////////////////////////////////////////////

void initRow(char *_ptr, const char *_s) {

    auto n = strlen(_s);
    strncpy(_ptr, _s, n);
}

void createField(Record *row, const char *arr[]) {

    Field *lastField = nullptr;
    for (int i = 0; i < row->count; i++) {

        auto *field = (Field *) malloc(sizeof(Field));

        if (lastField == nullptr) {

            row->fields = field;
        }
        field->size = strlen(arr[i]);
        field->type = (Type) i;
        memset(field->data, 0, 127);
        strncpy(field->data, arr[i], field->size);

        field->next = nullptr;
        if (lastField)
            lastField->next = field;
        lastField = field;
    }
}

void createField(Record *row) {

    Field *lastField = nullptr;
    for (int i = 0; i < row->count; i++) {

        auto *field = (Field *) malloc(sizeof(Field));

        if (lastField == nullptr) {

            row->fields = field;
        }
        memset(field->data, 0, 127);

        field->next = nullptr;
        if (lastField)
            lastField->next = field;
        lastField = field;
    }
}
/////////////////////////////////////////// Test methods ///////////////////////////////////////////////////////////////

//int main() {

//    return 0;
//}