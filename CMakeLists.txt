cmake_minimum_required(VERSION 3.16)
project(void_lib)
FIND_PACKAGE(VOID REQUIRED)  #VOID_LIB_PATH
include_directories($ENV{LIB})

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
set_project_options(project_options)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

if (CMAKE_CROSSCOMPILING)
    add_subdirectory(src)
else()
    add_subdirectory(tests)
endif()

