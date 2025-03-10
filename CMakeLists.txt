cmake_minimum_required(VERSION 3.30)
project(sdl3quake LANGUAGES C VERSION 0.1.0)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
	message(FATAL_ERROR "Only Clang is supported for this project, sorry!")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Generic" AND CMAKE_SYSTEM_PROCESSOR STREQUAL "wasm")
	include(${PROJECT_SOURCE_DIR}/cmake/progs.cmake)
else()
	include(${PROJECT_SOURCE_DIR}/cmake/engine.cmake)
endif()
