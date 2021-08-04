cmake_minimum_required(VERSION 3.19)
project(crc32_test)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/Config.cpp src/Serializer.cpp src/Deserializer.cpp src/CRC.cpp src/main.cpp src/Archive.cpp)

add_executable(crc32_test ${SOURCE_FILES}) #for source files

# target_include_directories must be added AFTER add_executable
target_include_directories(${PROJECT_NAME} PUBLIC headers) #for headers files

#add_subdirectory(test)