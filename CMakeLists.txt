cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# /camaroo/
# - /bin/
# - /build/
# - /camaroo-interpreter/
# ---- /src/ (.cpp)
# -------- main.cpp
# -------- something.cpp
# ---- /header/ (.h)
# -------- something.h
# -------- somethingelse.h
# - /camaroo-tests/

project(Camaroo CXX)
file (GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/camaroo-interpreter/src/**.cpp")
set (HEADER "${CMAKE_CURRENT_SOURCE_DIR}/camaroo-interpreter/header/")

add_executable(camaroo "${SOURCE}")
target_include_directories(camaroo PUBLIC "${HEADER}")
set_target_properties(camaroo
    PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Camaroo-Interpreter"
)
