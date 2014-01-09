add_executable(s_dynstr serialize/dyn_string/main.c)
target_link_libraries(s_dynstr
  ngine
)

# add_executable(s_list serialize/linked_list/main.c)
# target_link_libraries(s_list
#   ngine
# )

add_executable(s_np_struct serialize/nasted_ptr_struct//main.c)
target_link_libraries(s_np_struct
  ngine
)

add_subdirectory(serialize/dyn_string)
add_subdirectory(serialize/linked_list)
add_subdirectory(serialize/mesh)
add_subdirectory(serialize/nasted_ptr_struct)