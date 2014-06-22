cmake_minimum_required(VERSION 2.8)

project(numble)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

set(SOURCE_DIR "src")

set(CMAKE_MODULE_PATH "/usr/local/share/Logger/;/usr/local/share/MiscUtils/;/usr/local/share/SFML/cmake/Modules;${CMAKE_MODULE_PATH}")

set(EXECUTABLE_NAME "numble")

add_executable(${EXECUTABLE_NAME}
               ${SOURCE_DIR}/main.cpp)

find_package(Logger REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} Logger)

find_package(MiscUtils REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} MiscUtils)
