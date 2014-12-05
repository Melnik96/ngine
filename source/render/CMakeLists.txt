aux_source_directory("./" render_srcs)

add_library(ngine_render SHARED ${render_srcs} techs/gl44_tech.c)
target_link_libraries(ngine_render
  GLEW
  kazmath.so
)

install(TARGETS ngine_render LIBRARY DESTINATION /usr/local/lib)

add_subdirectory(raytrace)