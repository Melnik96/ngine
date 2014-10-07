aux_source_directory("./" network_srcs)

add_library(ngine_network SHARED ${network_srcs})
target_link_libraries(ngine_network
  pthread
)

install(TARGETS ngine_network LIBRARY DESTINATION /usr/local/lib)
