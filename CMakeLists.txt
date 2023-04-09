cmake_minimum_required(VERSION 3.24)
project(compathic)

set(CMAKE_CXX_STANDARD 17)

add_executable(compathic src/main.cpp src/commandHandler.cpp src/commandHandler.h src/botConfig.cpp src/botConfig.h)

find_package(argh)

target_link_libraries(compathic PRIVATE -ldpp -lconfig++ argh)