file(REMOVE_RECURSE
  "libcentering.pdb"
  "libcentering.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/centering.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
