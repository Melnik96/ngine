cmake_minimum_required(VERSION 2.8)

project(ngine)

include_directories("./source")

# add_definitions("-D__GNUC__")

set(ARCH "x86")
set(CMAKE_C_FLAGS "-std=gnu11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib/${ARCH}/ CACHE INTERNAL "" FORCE)

add_subdirectory(source)
add_subdirectory(tests)
