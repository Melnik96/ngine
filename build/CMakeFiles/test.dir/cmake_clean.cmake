FILE(REMOVE_RECURSE
  "CMakeFiles/test.dir/main.o"
  "../bin/test.pdb"
  "../bin/test"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/test.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
