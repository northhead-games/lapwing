cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project("lapwing")

add_executable(lapwing src/Main.cpp src/FileReader.cpp src/FileReader.h src/FileWriter.cpp src/FileWriter.h)

add_subdirectory(libraries/assimp)
add_subdirectory(libraries/nlohmann_json)

target_link_libraries(${PROJECT_NAME}
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE assimp
)