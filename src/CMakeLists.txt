cmake_minimum_required(VERSION 3.16)
project(BMW_Project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# ESP-IDF setup
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(BMW_Project)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Register component
idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS include)
