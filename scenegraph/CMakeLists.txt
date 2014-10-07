aux_source_directory("./" scenegraph_srcs)

add_library(ngine_scenegraph SHARED ${scenegraph_srcs})
# target_link_libraries(ngine_scenegraph)

install(TARGETS ngine_scenegraph LIBRARY DESTINATION /usr/local/lib)
