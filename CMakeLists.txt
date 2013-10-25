project(nuttyengine)

include_directories("source")

set(CMAKE_C_FLAGS "-std=c11")

aux_source_directory("source/" engine_sources)

add_library(nuttyengine SHARED ${engine_sources})
target_link_libraries(nuttyengine
  "GL"
  "GLEW"
  "glfw"
)

add_executable(test main.c)
target_link_libraries(test nuttyengine)

install(TARGETS nuttyengine LIBRARY DESTINATION lib)

add_subdirectory(source)