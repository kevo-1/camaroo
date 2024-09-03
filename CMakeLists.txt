# /camaroo/
# - /bin/
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

project(Camaroo CXX)
file (GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/camaroo_interpreter/src/**.cpp")
set (HEADER "${CMAKE_CURRENT_SOURCE_DIR}/camaroo_interpreter/header/")

add_executable(camaroo "${SOURCE}")
target_include_directories(camaroo PUBLIC "${HEADER}")
set_target_properties(camaroo
    PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Camaroo_Interpreter"
)

project(CamarooTests CXX)
file (GLOB_RECURSE TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/camaroo_tests/src/**.cpp")
set (TEST_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/camaroo_tests/header/")
set (CAMAROO_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/camaroo_interpreter/header/")

# GoogleTest stuff
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest")
set (GOOGLE_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/include")

add_executable(test_camaroo "${TEST_SOURCE}" "${SOURCE}")
target_link_libraries(test_camaroo PUBLIC gtest)
target_include_directories(test_camaroo PUBLIC "${TEST_HEADER}" "${CAMAROO_HEADER}" "${GOOGLE_HEADER}")
set_target_properties(test_camaroo
    PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Camaroo_Tests"
)
