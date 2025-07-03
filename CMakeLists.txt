# /camaroo/
# - /bin/
# ---- /BuildType/
# -------- Project-Platform-Architecture
# - /build/
# - /camaroo_interpreter/
# ---- /src/ (.cpp)
# -------- main.cpp
# -------- something.cpp
# ---- /header/ (.h)
# -------- something.h
# -------- somethingelse.h
# - /camaroo_tests/
# ---- /src/ (.cpp)
# -------- main.cpp
# -------- something.cpp
# ---- /header/ (.h)
# -------- something.h
# -------- somethingelse.h

cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(Camaroo)
# Set Build Type to Debug by default
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

# Set architecture to either 32 or 64 depending on system
set(ARCHITECTURE "32")
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ARCHITECTURE "64")
endif()

# OutputDir to be used for all projects
set(OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/camaroo_interpreter/")

option(BUILD_TESTS "Build tests for camaroo interpreter" ON)
if (BUILD_TESTS)
	add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/googletest")
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/camaroo_tests/")
endif()
