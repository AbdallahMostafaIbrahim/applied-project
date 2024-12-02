cmake_minimum_required(VERSION 3.0)
project(Sudoko_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})