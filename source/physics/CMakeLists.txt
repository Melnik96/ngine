aux_source_directory("./" physics_srcs)

include_directories("/usr/include/bullet")

add_library(ngine_physics SHARED ${physics_srcs} rb_bullet_api.cpp)
target_link_libraries(ngine_physics
  "/usr/lib/libBulletCollision.so"
  "/usr/lib/libBulletDynamics.so"
)

install(TARGETS ngine_physics LIBRARY DESTINATION /usr/local/lib)
