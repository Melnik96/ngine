cmake_minimum_required(VERSION 2.8)

project(ngine)

include_directories("./")
include_directories("scenegraph")

# add_definitions("-D__GNUC__")

set(ARCH "x86")
set(CMAKE_C_FLAGS "-std=c11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib/${ARCH}/ CACHE INTERNAL "" FORCE)

add_subdirectory(render)
add_subdirectory(scenegraph)
add_subdirectory(iohand)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(sound)
add_subdirectory(core)
add_subdirectory(tests)
add_subdirectory(import)
add_subdirectory(network)