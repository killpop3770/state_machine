#include <gtest/gtest.h>
#include "../crc32_test/headers/Config.h"
#include "../main.cpp"

TEST(SM, only_record_test) { // only record func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 0, 1, "name0"};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&record0, arr0);
    sm.createUpdateRecord(&record0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
//    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record0.id, record0_check.id);
    EXPECT_EQ(record0.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record0.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record0.count, record0_check.count);
    EXPECT_EQ(record0.type, record0_check.type);

    EXPECT_STREQ(record0.name, record0_check.name);
}

TEST(SM, one_setfield_create_record_test) { // 1 setfield func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 1, 1, "name0"};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&record0, arr0);
    sm.createUpdateRecord(&record0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record0.id, record0_check.id);
    EXPECT_EQ(record0.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record0.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record0.count, record0_check.count);
    EXPECT_EQ(record0.type, record0_check.type);

    EXPECT_STREQ(record0.name, record0_check.name);
    EXPECT_STREQ(record0.fields->data, record0_check.fields->data);
}

TEST(SM, three_setfield_create_record_test) { // 3 setField func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 3, 1, "name0"};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&record0, arr0);
    sm.createUpdateRecord(&record0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    strncpy(record0_check.fields->next->data, pRecord0_in_db->fields->next->data, pRecord0_in_db->fields->next->size);
    strncpy(record0_check.fields->next->next->data, pRecord0_in_db->fields->next->next->data,
            pRecord0_in_db->fields->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record0.id, record0_check.id);
    EXPECT_EQ(record0.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record0.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record0.count, record0_check.count);
    EXPECT_EQ(record0.type, record0_check.type);

    EXPECT_STREQ(record0.name, record0_check.name);
    EXPECT_STREQ(record0.fields->data, record0_check.fields->data);
    EXPECT_STREQ(record0.fields->next->data, record0_check.fields->next->data);
    EXPECT_STREQ(record0.fields->next->next->data, record0_check.fields->next->next->data);
}

TEST(SM, five_setfield_create_record_test) { // 5 setField func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 5, 1, "name0"};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "diem", "noctem"};
    createField(&record0, arr0);
    sm.createUpdateRecord(&record0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    strncpy(record0_check.fields->next->data, pRecord0_in_db->fields->next->data, pRecord0_in_db->fields->next->size);
    strncpy(record0_check.fields->next->next->data, pRecord0_in_db->fields->next->next->data,
            pRecord0_in_db->fields->next->next->size);
    strncpy(record0_check.fields->next->next->next->data, pRecord0_in_db->fields->next->next->next->data,
            pRecord0_in_db->fields->next->next->next->size);
    strncpy(record0_check.fields->next->next->next->next->data, pRecord0_in_db->fields->next->next->next->next->data,
            pRecord0_in_db->fields->next->next->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record0.id, record0_check.id);
    EXPECT_EQ(record0.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record0.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record0.count, record0_check.count);
    EXPECT_EQ(record0.type, record0_check.type);

    EXPECT_STREQ(record0.name, record0_check.name);
    EXPECT_STREQ(record0.fields->data, record0_check.fields->data);
    EXPECT_STREQ(record0.fields->next->data, record0_check.fields->next->data);
    EXPECT_STREQ(record0.fields->next->next->data, record0_check.fields->next->next->data);
    EXPECT_STREQ(record0.fields->next->next->next->data, record0_check.fields->next->next->next->data);
    EXPECT_STREQ(record0.fields->next->next->next->next->data, record0_check.fields->next->next->next->next->data);
}

TEST(SM, normal_update_record_test) { // update func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 4};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&record0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record1{15, 1001, false, 2021, 4};
    initRow(record1.name,
            "AlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234", "login_pid_1234", "diem"};
    createField(&record1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRecord(&record0);
    sm.createUpdateRecord(&record1);
    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    strncpy(record0_check.fields->next->data, pRecord0_in_db->fields->next->data, pRecord0_in_db->fields->next->size);
    strncpy(record0_check.fields->next->next->data, pRecord0_in_db->fields->next->next->data,
            pRecord0_in_db->fields->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////


    EXPECT_EQ(record1.id, record0_check.id);
    EXPECT_EQ(record1.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record1.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record1.count, record0_check.count);
    EXPECT_EQ(record1.type, record0_check.type);

    // only for comparing, because (record1.name + '\0') > 128
    std::string record1_name = record1.name;
    record1_name = record1_name.substr(0, 127);

    EXPECT_STREQ(record1_name.c_str(), record0_check.name);
    EXPECT_STREQ(record1.fields->data, record0_check.fields->data);
    EXPECT_STREQ(record1.fields->next->data, record0_check.fields->next->data);
    EXPECT_STREQ(record1.fields->next->next->data, record0_check.fields->next->next->data);
}

TEST(SM, increased_count_of_record_test) { // update with increased fields

    StateMachine sm;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 3};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234"};
    createField(&record0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record1{15, 1001, false, 2021, 4};
    initRow(record1.name,
            "AlexAlex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234", "login_pid_1234", "diem"};
    createField(&record1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRecord(&record0);
    sm.createUpdateRecord(&record1);
    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    record0_check.count = record1.count;
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    strncpy(record0_check.fields->next->data, pRecord0_in_db->fields->next->data, pRecord0_in_db->fields->next->size);
    strncpy(record0_check.fields->next->next->data, pRecord0_in_db->fields->next->next->data,
            pRecord0_in_db->fields->next->next->size);
    strncpy(record0_check.fields->next->next->next->data, pRecord0_in_db->fields->next->next->next->data,
            pRecord0_in_db->fields->next->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record1.id, record0_check.id);
    EXPECT_EQ(record1.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record1.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record1.count, record0_check.count);
    EXPECT_EQ(record1.type, record0_check.type);

    EXPECT_STREQ(record1.name, record0_check.name);
    EXPECT_STREQ(record1.fields->data, record0_check.fields->data);
    EXPECT_STREQ(record1.fields->next->data, record0_check.fields->next->data);
    EXPECT_STREQ(record1.fields->next->next->data, record0_check.fields->next->next->data);
    EXPECT_STREQ(record1.fields->next->next->next->data, record0_check.fields->next->next->next->data);

}

TEST(SM, decreased_count_of_record_test) { // update with decreased fields

    StateMachine sm;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 4};
    initRow(record0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "noctem"};
    createField(&record0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record1{15, 1001, false, 2021, 2};
    initRow(record1.name,
            "Alex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234"};
    createField(&record1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRecord(&record0);
    sm.createUpdateRecord(&record1);
    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};
    record0_check.count = record1.count;
    createField(&record0_check);

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    strncpy(record0_check.fields->data, pRecord0_in_db->fields->data, pRecord0_in_db->fields->size);
    strncpy(record0_check.fields->next->data, pRecord0_in_db->fields->next->data, pRecord0_in_db->fields->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record1.id, record0_check.id);
    EXPECT_EQ(record1.pid, record0_check.pid);
    EXPECT_EQ(record0.isDir, record0_check.isDir);
    EXPECT_EQ(record1.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record1.count, record0_check.count);
    EXPECT_EQ(record1.type, record0_check.type);

    EXPECT_STREQ(record1.name, record0_check.name);
    EXPECT_STREQ(record1.fields->data, record0_check.fields->data);
    EXPECT_STREQ(record1.fields->next->data, record0_check.fields->next->data);
    EXPECT_STREQ(record1.fields->next->next->data, record0_check.fields->next->next->data);

}

TEST(SM, delete_record_test) { // only record func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record0{15, 1111, false, 2020, 0, 1, "name0"};
    initRow(record0.name, "Ivan");
    sm.createUpdateRecord(&record0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record record1{15, 0, false, 0, 0, 0, "0"};
    initRow(record1.name, "0");
    sm.deleteRecord(15);
    sm.deleteRecord(15);
    sm.createUpdateRecord(&record1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRecord(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRecord0_in_db = sm.getRecord();
    Record record0_check{pRecord0_in_db->id, pRecord0_in_db->pid, pRecord0_in_db->isDir, pRecord0_in_db->lastUpdate,
                         pRecord0_in_db->count, pRecord0_in_db->type};

    strncpy(record0_check.name, pRecord0_in_db->name, strlen(pRecord0_in_db->name));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(record1.id, record0_check.id);
    EXPECT_EQ(record1.pid, record0_check.pid);
    EXPECT_EQ(record1.isDir, record0_check.isDir);
    EXPECT_EQ(record1.lastUpdate, record0_check.lastUpdate);
    EXPECT_EQ(record1.count, record0_check.count);
    EXPECT_EQ(record1.type, record0_check.type);

    EXPECT_STREQ(record1.name, record0_check.name);
}

//TEST(SM, deserialised_test) {
//    char ram[1024];
//    bool flag = ram[0];
//    uint8_t a = 12;
//    uint8_t b;
//    bool flag_to_ser = false;
//    bool flag_from_des = false;
//    Serializer ser(ram, 1024);
//    ser.serialize(flag_to_ser);
//    Deserializer des(ram, 1024);
//    des.deserialize(&flag_from_des);
//    EXPECT_EQ(flag_to_ser, flag_from_des);
//}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}