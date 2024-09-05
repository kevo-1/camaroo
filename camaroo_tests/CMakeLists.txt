project(CamarooTests CXX)
file (GLOB_RECURSE TEST_SOURCE "${CMAKE_SOURCE_DIR}/camaroo_tests/src/**.cpp")
file (GLOB_RECURSE CAMAROO_SOURCE "${CMAKE_SOURCE_DIR}/camaroo_interpreter/src/**.cpp")
list (REMOVE_ITEM CAMAROO_SOURCE "${CMAKE_SOURCE_DIR}/camaroo_interpreter/src/main.cpp")

set (TEST_HEADER "${CMAKE_SOURCE_DIR}/camaroo_tests/header/")
set (CAMAROO_HEADER "${CMAKE_SOURCE_DIR}/camaroo_interpreter/header/")

# GoogleTest stuff
set (GOOGLE_HEADER "${CMAKE_SOURCE_DIR}/third_party/googletest/include")

add_executable(test_camaroo "${TEST_SOURCE}" "${CAMAROO_SOURCE}")
target_link_libraries(test_camaroo PRIVATE gtest)
target_include_directories(test_camaroo PRIVATE "${TEST_HEADER}" "${CAMAROO_HEADER}" "${GOOGLE_HEADER}")
