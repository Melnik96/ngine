cmake_minimum_required(VERSION 2.8)

project(ngine)

include_directories("source")
include_directories("source/math/")
include_directories("source/import/blender/")

set(ARCH "x86")
set(CMAKE_C_FLAGS "-std=c11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/editor/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/lib/${ARCH}/ CACHE INTERNAL "" FORCE)

aux_source_directory("source/" engine_sources)
aux_source_directory("source/cntr" engine_sources_cntr)
aux_source_directory("source/math" engine_sources_math)
set(engine_sources
  ${engine_sources} 
  ${engine_sources_cntr} 
  ${engine_sources_math}
)

add_library(ngine SHARED ${engine_sources})
target_link_libraries(ngine
  "GL"
  "GLEW"
  "glfw"
  "pthread"
)

add_executable(neditor editor/source/net.c editor/source/main.c)
target_link_libraries(neditor
  ngine
)

# install(TARGETS ngine LIBRARY DESTINATION lib)

add_subdirectory(examples)

add_subdirectory(source/physics)