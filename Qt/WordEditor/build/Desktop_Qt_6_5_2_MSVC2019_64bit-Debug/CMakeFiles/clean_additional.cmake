# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WordEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WordEditor_autogen.dir\\ParseCache.txt"
  "WordEditor_autogen"
  )
endif()
