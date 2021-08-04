#include <iostream>
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
    char data[128]{};
    enum Type type{};
    uint8_t size{};

    Field *next = nullptr;
};

static Field fields_test[3]; // for tests

struct Record {
    uint16_t id{};
    uint16_t pid{};
    bool isDir{};
    uint32_t lastUpdate{};
    uint8_t count{};
    uint8_t type = 1;
    char name[128]{};

    Field *fields{};
};

/// ConfigSectionDescriptor<Row> specialization.
template<>
struct ConfigSectionDescriptor<Record> {

    template<class Archive>
    static constexpr auto pack(Archive &&ar, Record &x) {

        return ar & x.id & x.pid & x.isDir & x.lastUpdate & x.count & x.type;
        // & x.name
    }
};

const uint16_t db_size = 20; // Size of database
const uint16_t row_size = 1024; // Size of row
static char database[db_size][row_size]; // new serialized database

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

    bool begin(Record *newRow) {

        if (not beginState)
            return false;

        index = findBlock(newRow->id, &pBlock);

        if (index == -1) {
            return false;
        } else if (index >= 0) {
            reserve();

            m_record->id = newRow->id;
            m_record->pid = newRow->pid;
            m_record->isDir = newRow->isDir;
            m_record->lastUpdate = newRow->lastUpdate;
            m_record->type = newRow->type;
            memset(m_record->name, 0, 128);
            uint16_t name_len = normalizeLen(newRow->name, 127);
            strncpy(m_record->name, newRow->name, name_len);
            m_record->count = newRow->count;
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

//    bool setField(Field *field, Type type, const char *data) {
//        assert(field != nullptr);
//
//        if (not m_record->isDir and not beginState) {
//            field->type = type;
//            field->size = normalizeLen(data, 127);
//            memset(field->data, 0, 128);
//            strncpy(field->data, data, field->size);
//
//            field->next = nullptr; // присвоение адреса предыдущему полю
//            if (m_lastField)
//                m_lastField->next = field;
//
//            m_lastField = field;
//            return true;
//        }
//        return false;
//    } <--deprecated setField version!

    bool end(bool commit) {

        if (not m_record and not beginState)
            return false;

        if (commit) {
            Serializer ser(pBlock, row_size);
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


    bool readRow(uint16_t id) {

        index = findBlock(id, &pBlock);

        if (index == -1) {
            return false;
        } else if (index >= 0) {
            reserve();
            Deserializer des(pBlock, row_size);
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

    uint16_t createUpdateRow(Record *newRow) {

        if (newRow == nullptr)
            return -1;

        if (begin(newRow)) {
            auto *tail = newRow->fields;

            for (int i = 0; i < newRow->count; i++) {
                setField(tail);
                tail = tail->next;
            }

            m_lastField = nullptr;
            end(true);
        }

        return newRow->id;
    }

    void deleteRow(uint16_t id) {

        Deserializer des(pBlock, sizeof(uint32_t));
        Serializer ser(pBlock, sizeof(uint32_t));
        uint32_t mag0 = 0;

        des.deserialize(&mag0);
        mag0 = 0;
        ser.serialize(mag0);
    }


    ////////////// Only for tests ////////////
    [[nodiscard]] size_t getIndex() const {
        return index;
    }

    Record *getRecord() { return m_record; }

    void resetM_Record() {
        m_record->id = 0;
        m_record->pid = 0;
        m_record->isDir = false;
        m_record->lastUpdate = 0;
        m_record->count = 0;
        m_record->type = 0;
        memset(m_record->fields->data, 0, 128);
        memset(m_record->fields->next->data, 0, 128);
        memset(m_record->fields->next->next->data, 0, 128);
    }
    ////////////// Only for tests ////////////

private:
    struct Record record{};

    Record *m_record = &record;
    Field *m_lastField = nullptr;

    char *pBlock = nullptr;
    size_t index = 0;
    bool beginState = true;
    uint8_t count = 0;
};


/////////////////////////////////////////// Test methods ///////////////////////////////////////////////////////////////
//static size_t cnt_for_test = 0; // only for test functions
//
//void printRecord(StateMachine sm, uint16_t id) {
//    uint16_t len0 = 0;
//    const char *type_name[3] = {"URL", "PASSWORD", "LOGIN"};
//
//    sm.readRow(id);
//    Record *rec = sm.getRecord();
//    len0 = strlen(rec->name);
//
//    std::cout << "==========================================" << std::endl;
//    std::cout << "id:         " << rec->id << std::endl;
//    std::cout << "pid:        " << rec->pid << std::endl;
//    std::cout << "isDir:      " << std::boolalpha << rec->isDir << std::endl;
//    std::cout << "type:       " << (int) rec->type << std::endl;
//    std::cout << "count:      " << (int) rec->count << std::endl;
//    std::cout << "lastUpdate: " << rec->lastUpdate << std::endl;
//    std::cout << "name:       ";
//    for (int j = 0; j < (int) len0; j++)
//        printf("%c", rec->name[j]);
//    std::cout << std::endl;
//    std::cout << "==========================================" << std::endl;
//
//    Field *pField = rec->fields;
//    int i = 0;
//    while (i < rec->count) {
//        std::cout << "Field #" << std::endl;
//        std::cout << "Data: ";
//        for (int j = 0; j < (int) pField->size; j++)
//            printf("%c", pField->data[j]);
//        std::cout << std::endl;
//        std::cout << "Size: " << (int) pField->size << std::endl;
//        std::cout << "Type: " << type_name[pField->type] << std::endl;
//        std::cout << "Next: " << pField->next << std::endl;
//        std::cout << std::endl;
//        pField = pField->next;
//        i++;
//    }
//}
//
//void create_update_func_test(StateMachine &sm, Record *row) {
//    std::cout << "TEST " << cnt_for_test << std::endl;
//    sm.createUpdateRow(row);
//    cnt_for_test++;
//}
//
//void begin_func_test(StateMachine sm, Record *newRow) {
//    sm.begin(newRow);
//    if (not sm.begin(newRow)) {
//        std::cout << "==========================================" << std::endl;
//        std::cout << "begin_func_test:  It's ok!" << std::endl;
//    } else {
//        std::cout << "==========================================" << std::endl;
//        std::cout << "begin_func_test:  Fault!" << std::endl;
//    }
//}
//
//void setFields_func_test(StateMachine sm, Record *newRow) {
////    sm.setField(&newRow->fields[URL], URL, "some_data");
////    sm.setField(&newRow->fields[URL], URL, "some_data");
////    sm.setBeginState(true);
////    if (not sm.setField(&newRow->fields[URL], URL, "some_data")) {
////        std::cout << "==========================================" << std::endl;
////        std::cout << "setFields_func_test: It's ok!" << std::endl;
////    } else {
////        std::cout << "==========================================" << std::endl;
////        std::cout << "setFields_func_test: Fault!" << std::endl;
////    }
//}
//
//
//void test_create(Serializer *ser, int i) {
//    Record row;
//
//    row.id = i + 6; // id > 0
//    row.pid = 400 + i;
//    row.isDir = false;
//    row.lastUpdate = 2009 + i;
//    row.count = 3;
//
//    const char *arr[] = {"https://test.com", "my_password", "my_login"};
//    createField(&row, arr);
//    initRow(row.name, "my_name");
//
//    ser->serialize(mag);
//    ConfigSectionDescriptor<Record>::pack(*ser, row);
//}
//
//void findRow_func_test(StateMachine &sm, uint16_t id) {
////    bool *pBlock;
//////    char *record0 = sm.getRecord();
////    findBlock(id, pBlock);
////    if (not isNewRow) {
////        std::cout << "==========================================" << std::endl;
////        std::cout << "findRow_func_test:    Fault!" << std::endl;
////    } else {
////        std::cout << "==========================================" << std::endl;
////        std::cout << "findRow_func_test:    It's ok!" << std::endl;
////    }
//} <-- deprecated tests version

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
//
////     Initialize db
//    for (int i = 0; i < 10; i++) {
//        Serializer ser(database[i], row_size);
//        test_create(&ser, i);
//    }
//
//    // Data for tests
//    Record row0{15, 1111, false, 2020, 4};
//    initRow(row0.name, "Ivan");
//    const char *arr[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
//    createField(&row0, arr);
//
//    Record row1{16, 1111, false, 2020, 4};
//    initRow(row1.name, "AlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlex");
//    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234", "login_pid_1234", "diem"};
//    createField(&row1, arr1);
//
//    Record row2{16, 1000, false, 2000, 3};
//    initRow(row2.name, "Rick");
//    const char *arr2[] = {"https://buhtig.io", "password_1234", "login_1234"};
//    createField(&row2, arr2);
//
//    Record row3{16, 1010, false, 2010, 3};
//    initRow(row3.name, "Nick");
//    const char *arr3[] = {"https://asdffdsaasdf.com/index", "pass_pass_pass_pass", ""};
//    createField(&row3, arr3);
//
//    Record row4{16, 1011, true, 2012, 3};
//    initRow(row4.name, "Gick");
//    const char *arr4[] = {"https://asdffdsaasdffdsaasdf.com/asdffdsaasdffdsaindex.html", "pass_pass_pass_pass_pass_pass_pass_pass_pass_pass_pass_pass", "login"};
//    createField(&row4, arr4);
//
//    Record row5{16, 100, false, 1000, 3};
//    initRow(row5.name, "Alex0");
//    const char *arr5[] = {"https://n&tw0rk.c0m", "pass0", "log0"};
//    createField(&row5, arr5);
//
//    StateMachine sm;
//
//    ///////////////// TESTs ///////////////////
//    create_update_func_test(sm, &row0);
//    sm.resetM_Record();
//    printRecord(sm,15);
//    create_update_func_test(sm, &row1);
////    printRecord(sm,16);
////    create_update_func_test(sm, &row2);
////    printRecord(sm,16);
////    create_update_func_test(sm, &row3);
////    printRecord(sm,16);
////    create_update_func_test(sm, &row4);
////    printRecord(sm,16);
////    create_update_func_test(sm, &row5);
////    printRecord(sm,16);
//
////
////    begin_func_test(sm, &row1);
////
////    setFields_func_test(sm, &row6);
////
////    findRow_func_test(sm, 17);
//    ///////////////////////////////////////////
//
//    return 0;
//} <-- deprecated main func