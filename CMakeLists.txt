cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project("lapwing")

add_executable(lapwing "src/lapwing.cpp" "src/lapwing.h" "src/reader.cpp" "src/reader.h" "src/endian.h"
        "src/endian.cpp" "src/hasher.h" "src/hasher.cpp" "src/writer.cpp" "src/stb_image.h" "src/writer.h")

add_subdirectory(libraries/assimp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE assimp
)