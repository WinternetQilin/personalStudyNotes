# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\audioAndVideo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\audioAndVideo_autogen.dir\\ParseCache.txt"
  "audioAndVideo_autogen"
  )
endif()
