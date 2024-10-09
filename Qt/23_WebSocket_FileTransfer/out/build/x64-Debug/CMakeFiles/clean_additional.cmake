# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Client\\CMakeFiles\\Client_autogen.dir\\AutogenUsed.txt"
  "Client\\CMakeFiles\\Client_autogen.dir\\ParseCache.txt"
  "Client\\Client_autogen"
  "Server\\CMakeFiles\\Server_autogen.dir\\AutogenUsed.txt"
  "Server\\CMakeFiles\\Server_autogen.dir\\ParseCache.txt"
  "Server\\Server_autogen"
  )
endif()
