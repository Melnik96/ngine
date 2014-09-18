add_executable(serialize
  main.c
  a_serialize.c
)

target_link_libraries(serialize ngine_core)