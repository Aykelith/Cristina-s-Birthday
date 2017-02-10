cmake_minimum_required(VERSION 2.8)
project ("XALGame")

# VERSION
################################################################################
set(XALGAME_MAJOR_VERSION 0)
set(XALGAME_MINOR_VERSION 0)
set(XALGAME_REVISION_VERSION 1)
################################################################################

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# REQUIRED LIBRARIES
################################################################################
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# SFML
set(SFML_ROOT "E:/Programming/Desktop/Libraries/SFML" "E:/Programming/Desktop/Libraries/SFML/builds/mingw63")

find_package(SFML 2.4.1 REQUIRED system window graphics)
#find_package(Thor 2)
#####################################################1###########################

set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/extlibs/headers")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

file(
        GLOB_RECURSE
        SOURCES
        ${SOURCE_PATH}/*
)

include_directories(${INCLUDE_PATH})
#include_directories(${THOR_INCLUDE_DIR} "E:/Work/Programare/Libs/Thor/extlibs/aurora/include")
#include_directories("${PROJECT_SOURCE_DIR}/extlibs/headers")
#include_directories("E:/Work/Programare/Libs/lua-5.3.2/src")
include_directories(${SFML_INCLUDE_DIR})

# Compiler settings
################################################################################
# Detect compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(USING_GCC TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(USING_CLANG TRUE)
endif()

# For GCC and Clang, enable C++11 support and add some other flags
if(USING_GCC OR USING_CLANG)
  add_compile_options(-std=c++14 -pedantic -Wall)
endif()
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(
        "XALGame"
        ${SOURCES}
)

target_link_libraries(XALGame
	${SFML_LIBRARIES}
)
