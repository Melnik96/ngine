aux_source_directory("./" iohand_srcs)

add_library(ngine_iohand SHARED ${iohand_srcs} ./intern/glfw/glfw_iohand.c)
target_link_libraries(ngine_iohand
  glfw
)

install(TARGETS ngine_iohand LIBRARY DESTINATION /usr/local/lib)
