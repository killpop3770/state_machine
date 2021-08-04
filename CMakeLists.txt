cmake_minimum_required(VERSION 3.19)
project(state_machine)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES crc32_test/src/Serializer.cpp crc32_test/src/Deserializer.cpp crc32_test/src/Config.cpp crc32_test/src/CRC.cpp crc32_test/src/Archive.cpp)

add_library(Archive crc32_test/src/Serializer.cpp crc32_test/src/Deserializer.cpp crc32_test/src/Archive.cpp)

add_executable(state_machine main.cpp ${SOURCE_FILES})

add_subdirectory(crc32_test)

target_include_directories(${PROJECT_NAME} PUBLIC crc32_test/headers/)

add_subdirectory(test)