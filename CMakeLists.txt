cmake_minimum_required(VERSION 2.8)

project(nuttyengine)

include_directories("source")
include_directories("source/math/")
include_directories("source/import/blender/")

set(ARCH "x86")
set(CMAKE_C_FLAGS "-std=c11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/lib/${ARCH}/ CACHE INTERNAL "" FORCE)

aux_source_directory("source/" engine_sources)

add_library(nuttyengine SHARED ${engine_sources})
target_link_libraries(nuttyengine
  "GL"
  "GLEW"
  "glfw"
  "../bin/lib/${ARCH}/libSIMDx86.a"
)

add_executable(ne_test main.c)
target_link_libraries(ne_test nuttyengine)

install(TARGETS nuttyengine LIBRARY DESTINATION lib)

add_subdirectory(source)