project(CamarooInterpreter CXX)
file (GLOB_RECURSE SOURCE "${CMAKE_SOURCE_DIR}/camaroo_interpreter/src/**.cpp")
set (HEADER "${CMAKE_SOURCE_DIR}/camaroo_interpreter/header/")

add_executable(camaroo "${SOURCE}")
target_include_directories(camaroo PUBLIC "${HEADER}")
