# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "UPM-Server\\CMakeFiles\\UPM-Server_autogen.dir\\AutogenUsed.txt"
  "UPM-Server\\CMakeFiles\\UPM-Server_autogen.dir\\ParseCache.txt"
  "UPM-Server\\UPM-Server_autogen"
  "Util\\CMakeFiles\\Util_autogen.dir\\AutogenUsed.txt"
  "Util\\CMakeFiles\\Util_autogen.dir\\ParseCache.txt"
  "Util\\Util_autogen"
  )
endif()
