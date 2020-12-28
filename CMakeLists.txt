cmake_minimum_required(VERSION 2.8)

project(stateflow CXX C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)

option(SF_BUILD_TEST "Build unit test (require Catch2)" ON)

set(sf_include_dirs ${PROJECT_SOURCE_DIR})

if(SF_BUILD_TEST)
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/Catch2)
    add_subdirectory(unit_test)
endif()
