cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(disasm VERSION 0.1)

add_definitions(-DFILE_INPUT)

file(GLOB SOURCES "*.cc")
file(GLOB HEADERS "*.h")

add_executable(disasm ${SOURCES} ${HEADERS})
