cmake_minimum_required(VERSION 2.8)

project(ngine)

include_directories("source")
include_directories("source/math/")
include_directories("source/import/blender/")
include_directories("/usr/include/bullet/")

# add_definitions("-D__GNUC__")

set(ARCH "x86")
set(CMAKE_C_FLAGS "-std=c11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/neditor/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/lib/${ARCH}/ CACHE INTERNAL "" FORCE)

aux_source_directory("source/" engine_sources)
aux_source_directory("source/cntr" engine_sources_cntr)
aux_source_directory("source/math" engine_sources_math)
aux_source_directory("source/render" engine_sources_render)
aux_source_directory("source/iohand" engine_sources_iohand)
set(engine_sources
  ${engine_sources} 
  ${engine_sources_cntr} 
  ${engine_sources_math}
  ${engine_sources_render}
  ${engine_sources_iohand}
  source/import/obj/obj.c
  source/import/obj/awol/awol.c
  source/import/targa/tga.c
  source/physics/rigidbody/rb_bullet_api.cpp
)

add_library(ngine SHARED ${engine_sources})
target_link_libraries(ngine
  "GL"
  "GLEW"
  "glfw"
  "fmodex"
  "libBulletCollision.so"
  "libBulletDynamics.so"
  "kazmath.so"
  "pthread"
  "tcc"
  "dl"
)

add_executable(neditor neditor/source/neditor.c neditor/source/main.c)
target_link_libraries(neditor
  ngine
)

# install(TARGETS ngine LIBRARY DESTINATION lib)

add_subdirectory(examples)

add_subdirectory(source/import/obj)
add_subdirectory(source/anim)
add_subdirectory(source/cmdinterp)
add_subdirectory(source/import/targa)
# add_subdirectory(source/import/blender)
add_subdirectory(neditor/bin/scripts)
add_subdirectory(source/nodes)
add_subdirectory(tools)