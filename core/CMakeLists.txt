aux_source_directory("./" ngine_core_src)

add_library(ngine_core SHARED ${ngine_core_src})

install(TARGETS ngine_core LIBRARY DESTINATION /usr/local/lib)
