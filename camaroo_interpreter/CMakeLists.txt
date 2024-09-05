project(CamarooInterpreter CXX)

file(GLOB_RECURSE SOURCE "${CMAKE_SOURCE_DIR}/camaroo_interpreter/src/**.cpp")
set(HEADER "${CMAKE_SOURCE_DIR}/camaroo_interpreter/header/")
set(BIN_NAME "camaroo-${CMAKE_SYSTEM_NAME}-${ARCHITECTURE}")

add_executable(${BIN_NAME} "${SOURCE}")
target_include_directories(${BIN_NAME} PUBLIC "${HEADER}")
set_target_properties(${BIN_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${OutputDir}"
)
