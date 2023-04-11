cmake_minimum_required(VERSION 3.24)
project(compathic)

set(CMAKE_CXX_STANDARD 17)

add_executable(compathic src/main.cpp src/commandHandler.cpp src/commandHandler.h src/botConfig.cpp src/botConfig.h src/commands/command.h src/commands/command.cpp src/commands/pingCommand.cpp src/commands/pingCommand.h)

find_package(argh)
find_package(fmt)

target_link_libraries(compathic PRIVATE -ldpp -lconfig++ argh fmt::fmt)