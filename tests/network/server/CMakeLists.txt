add_executable(test_server main.c)
target_link_libraries(test_server
  ngine_network
  pthread
)
