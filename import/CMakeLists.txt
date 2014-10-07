add_library(ngine_import SHARED obj/obj.c)
target_link_libraries(ngine_import
  assimp
)

install(TARGETS ngine_import LIBRARY DESTINATION /usr/local/lib)
