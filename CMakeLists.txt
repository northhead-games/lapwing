cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project("lapwing")

add_executable(${PROJECT_NAME} "src/lapwing.cpp" "src/reader.cpp" "src/reader.h" "src/endian.h"
        "src/endian.cpp" "src/hasher.h" "src/hasher.cpp" "src/writer.cpp"  "src/writer.h"
        "src/file_utils.h" "src/file_utils.cpp")

add_subdirectory(libraries/header_libs)

target_include_directories(${PROJECT_NAME}
	PUBLIC include/
    PUBLIC libraries/header_libs/include
)
