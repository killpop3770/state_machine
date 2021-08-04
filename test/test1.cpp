#include <iostream>
#include <gtest/gtest.h>
#include "../crc32_test/headers/Config.h"
#include "../main.cpp"

TEST(SM, only_record_test) { // only record func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 0, 1, "name0"};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&row0, arr0);
    sm.createUpdateRow(&row0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
//    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row0.id, row0_check.id);
    EXPECT_EQ(row0.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row0.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row0.count, row0_check.count);
    EXPECT_EQ(row0.type, row0_check.type);

    EXPECT_STREQ(row0.name, row0_check.name);
}

TEST(SM, one_setfield_create_row_test) { // 1 setfield func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 1, 1, "name0"};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&row0, arr0);
    sm.createUpdateRow(&row0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row0.id, row0_check.id);
    EXPECT_EQ(row0.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row0.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row0.count, row0_check.count);
    EXPECT_EQ(row0.type, row0_check.type);

    EXPECT_STREQ(row0.name, row0_check.name);
    EXPECT_STREQ(row0.fields->data, row0_check.fields->data);
}

TEST(SM, three_setfield_create_row_test) { // 3 setField func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 3, 1, "name0"};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&row0, arr0);
    sm.createUpdateRow(&row0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    strncpy(row0_check.fields->next->data, pRow0_in_db->fields->next->data, pRow0_in_db->fields->next->size);
    strncpy(row0_check.fields->next->next->data, pRow0_in_db->fields->next->next->data,
            pRow0_in_db->fields->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row0.id, row0_check.id);
    EXPECT_EQ(row0.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row0.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row0.count, row0_check.count);
    EXPECT_EQ(row0.type, row0_check.type);

    EXPECT_STREQ(row0.name, row0_check.name);
    EXPECT_STREQ(row0.fields->data, row0_check.fields->data);
    EXPECT_STREQ(row0.fields->next->data, row0_check.fields->next->data);
    EXPECT_STREQ(row0.fields->next->next->data, row0_check.fields->next->next->data);
}

TEST(SM, five_setfield_create_row_test) { // 5 setField func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 5, 1, "name0"};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "diem", "noctem"};
    createField(&row0, arr0);
    sm.createUpdateRow(&row0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    strncpy(row0_check.fields->next->data, pRow0_in_db->fields->next->data, pRow0_in_db->fields->next->size);
    strncpy(row0_check.fields->next->next->data, pRow0_in_db->fields->next->next->data,
            pRow0_in_db->fields->next->next->size);
    strncpy(row0_check.fields->next->next->next->data, pRow0_in_db->fields->next->next->next->data,
            pRow0_in_db->fields->next->next->next->size);
    strncpy(row0_check.fields->next->next->next->next->data, pRow0_in_db->fields->next->next->next->next->data,
            pRow0_in_db->fields->next->next->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row0.id, row0_check.id);
    EXPECT_EQ(row0.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row0.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row0.count, row0_check.count);
    EXPECT_EQ(row0.type, row0_check.type);

    EXPECT_STREQ(row0.name, row0_check.name);
    EXPECT_STREQ(row0.fields->data, row0_check.fields->data);
    EXPECT_STREQ(row0.fields->next->data, row0_check.fields->next->data);
    EXPECT_STREQ(row0.fields->next->next->data, row0_check.fields->next->next->data);
    EXPECT_STREQ(row0.fields->next->next->next->data, row0_check.fields->next->next->next->data);
    EXPECT_STREQ(row0.fields->next->next->next->next->data, row0_check.fields->next->next->next->next->data);
}

TEST(SM, normal_update_row_test) { // update func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 4};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "sone"};
    createField(&row0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row1{15, 1001, false, 2021, 4};
    initRow(row1.name,
            "AlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlexAlex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234", "login_pid_1234", "diem"};
    createField(&row1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRow(&row0);
    sm.createUpdateRow(&row1);
    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    strncpy(row0_check.fields->next->data, pRow0_in_db->fields->next->data, pRow0_in_db->fields->next->size);
    strncpy(row0_check.fields->next->next->data, pRow0_in_db->fields->next->next->data,
            pRow0_in_db->fields->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////


    EXPECT_EQ(row1.id, row0_check.id);
    EXPECT_EQ(row1.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row1.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row1.count, row0_check.count);
    EXPECT_EQ(row1.type, row0_check.type);

    // only for comparing, because (row1.name + '\0') > 128
    std::string row1_name = row1.name;
    row1_name = row1_name.substr(0, 127);

    EXPECT_STREQ(row1_name.c_str(), row0_check.name);
    EXPECT_STREQ(row1.fields->data, row0_check.fields->data);
    EXPECT_STREQ(row1.fields->next->data, row0_check.fields->next->data);
    EXPECT_STREQ(row1.fields->next->next->data, row0_check.fields->next->next->data);
}

TEST(SM, increased_count_of_row_test) { // update with increased fields

    StateMachine sm;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 3};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234"};
    createField(&row0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row1{15, 1001, false, 2021, 4};
    initRow(row1.name,
            "AlexAlex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234", "login_pid_1234", "diem"};
    createField(&row1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRow(&row0);
    sm.createUpdateRow(&row1);
    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    row0_check.count = row1.count;
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    strncpy(row0_check.fields->next->data, pRow0_in_db->fields->next->data, pRow0_in_db->fields->next->size);
    strncpy(row0_check.fields->next->next->data, pRow0_in_db->fields->next->next->data,
            pRow0_in_db->fields->next->next->size);
    strncpy(row0_check.fields->next->next->next->data, pRow0_in_db->fields->next->next->next->data,
            pRow0_in_db->fields->next->next->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row1.id, row0_check.id);
    EXPECT_EQ(row1.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row1.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row1.count, row0_check.count);
    EXPECT_EQ(row1.type, row0_check.type);

    EXPECT_STREQ(row1.name, row0_check.name);
    EXPECT_STREQ(row1.fields->data, row0_check.fields->data);
    EXPECT_STREQ(row1.fields->next->data, row0_check.fields->next->data);
    EXPECT_STREQ(row1.fields->next->next->data, row0_check.fields->next->next->data);
    EXPECT_STREQ(row1.fields->next->next->next->data, row0_check.fields->next->next->next->data);

}

TEST(SM, decreased_count_of_row_test) { // update with decreased fields

    StateMachine sm;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 4};
    initRow(row0.name, "Ivan");
    const char *arr0[] = {"https://github.com", "password_pid_1234", "login_pid_1234", "noctem"};
    createField(&row0, arr0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row1{15, 1001, false, 2021, 2};
    initRow(row1.name,
            "Alex");
    const char *arr1[] = {"https://buhtig.moc", "password_pid_1234"};
    createField(&row1, arr1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.createUpdateRow(&row0);
    sm.createUpdateRow(&row1);
    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};
    row0_check.count = row1.count;
    createField(&row0_check);

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    strncpy(row0_check.fields->data, pRow0_in_db->fields->data, pRow0_in_db->fields->size);
    strncpy(row0_check.fields->next->data, pRow0_in_db->fields->next->data, pRow0_in_db->fields->next->size);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row1.id, row0_check.id);
    EXPECT_EQ(row1.pid, row0_check.pid);
    EXPECT_EQ(row0.isDir, row0_check.isDir);
    EXPECT_EQ(row1.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row1.count, row0_check.count);
    EXPECT_EQ(row1.type, row0_check.type);

    EXPECT_STREQ(row1.name, row0_check.name);
    EXPECT_STREQ(row1.fields->data, row0_check.fields->data);
    EXPECT_STREQ(row1.fields->next->data, row0_check.fields->next->data);
    EXPECT_STREQ(row1.fields->next->next->data, row0_check.fields->next->next->data);

}

TEST(SM, delete_record_test) { // only record func

    StateMachine sm;
    // Data for tests
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row0{15, 1111, false, 2020, 0, 1, "name0"};
    initRow(row0.name, "Ivan");
    sm.createUpdateRow(&row0);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record row1{15, 0, false, 0, 0, 0, "0"};
    initRow(row1.name, "0");
    sm.deleteRow(15);
    sm.deleteRow(15);
    sm.createUpdateRow(&row1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sm.readRow(15);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Record *pRow0_in_db = sm.getRecord();
    Record row0_check{pRow0_in_db->id, pRow0_in_db->pid, pRow0_in_db->isDir, pRow0_in_db->lastUpdate,
                      pRow0_in_db->count, pRow0_in_db->type};

    strncpy(row0_check.name, pRow0_in_db->name, strlen(pRow0_in_db->name));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    EXPECT_EQ(row1.id, row0_check.id);
    EXPECT_EQ(row1.pid, row0_check.pid);
    EXPECT_EQ(row1.isDir, row0_check.isDir);
    EXPECT_EQ(row1.lastUpdate, row0_check.lastUpdate);
    EXPECT_EQ(row1.count, row0_check.count);
    EXPECT_EQ(row1.type, row0_check.type);

    EXPECT_STREQ(row1.name, row0_check.name);
}

//TEST(SM, deserialised_test) {
//
//    char ram[1024];
//    bool flag = ram[0];
//
//    uint8_t a = 12;
//    uint8_t b;
//
//    bool flag_to_ser = false;
//    bool flag_from_des = false;
//
//    Serializer ser(ram, 1024);
//    ser.serialize(flag_to_ser);
//
//    Deserializer des(ram, 1024);
//    des.deserialize(&flag_from_des);
//
//    EXPECT_EQ(flag_to_ser, flag_from_des);
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}