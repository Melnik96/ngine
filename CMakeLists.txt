project(nuttyengine)

include_directories("source")

add_executable(nuttyengine source/scene.c source/serialization.c source/physics_mgr.c source/dynlib.c source/math.c source/camera.c source/scene_object.c source/entity.c source/mesh.c main.cpp)

install(TARGETS nuttyengine RUNTIME DESTINATION bin)

add_subdirectory(source)