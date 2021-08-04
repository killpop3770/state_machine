cmake_minimum_required(VERSION 3.19)

project(Google_tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES ../crc32_test/src/Serializer.cpp ../crc32_test/src/Deserializer.cpp )

#include_directories({PROJECT_NAME} ../crc32_test/headers)

add_executable(Google_Tests_run test1.cpp ${SOURCE_FILES})

target_link_libraries(Google_Tests_run gtest gtest_main Archive)
