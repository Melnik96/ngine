aux_source_directory("./" mesh_srcs)

add_library(ngine_mesh SHARED ${mesh_srcs})
# target_link_libraries(ngine_mesh)

install(TARGETS ngine_mesh LIBRARY DESTINATION /usr/local/lib)
