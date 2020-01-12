file(REMOVE_RECURSE
  "liblogger.pdb"
  "liblogger.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/logger.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
