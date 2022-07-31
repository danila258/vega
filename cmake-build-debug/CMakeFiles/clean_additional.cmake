# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Backend/OpenXLSX/CMakeFiles/OpenXLSX_autogen.dir/AutogenUsed.txt"
  "Backend/OpenXLSX/CMakeFiles/OpenXLSX_autogen.dir/ParseCache.txt"
  "Backend/OpenXLSX/OpenXLSX_autogen"
  "CMakeFiles/Vega_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Vega_autogen.dir/ParseCache.txt"
  "Vega_autogen"
  )
endif()
