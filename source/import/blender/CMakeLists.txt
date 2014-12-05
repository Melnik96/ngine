include_directories("blenkernel/")
include_directories("blenloader/")
include_directories("makesdna/")
include_directories("blenlib/")
include_directories("guardedalloc/")
include_directories("blenfont/")

aux_source_directory("blenkernel/intern/" blenkernel)
aux_source_directory("blenloader/intern/" blenloader)
aux_source_directory("makesdna/intern/" makesdna)
aux_source_directory("guardedalloc/intern/" guardedalloc)
aux_source_directory("blenfont/intern/" blenfont)

add_executable(blen_test 
  main.c
#   blen_mesh.c
#   blen_sc_obj.c
#   blen_scene.c
  ${blenkernel}
  ${blenloader}
  ${makesdna}
  ${guardedalloc}
  ${blenfont}
)