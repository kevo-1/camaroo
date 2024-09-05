# /camaroo/
# - /bin/
# - /bin-int/
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
option(BUILD_TESTS "Build tests for camaroo interpreter" ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")
set(CMAKE_RUNTIME_ARCHIVE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/camaroo_interpreter/")

if (BUILD_TESTS)
	add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/googletest")
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/camaroo_tests/")
endif()
