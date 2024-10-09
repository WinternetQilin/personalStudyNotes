# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "SJwt\\CMakeFiles\\SJwt_autogen.dir\\AutogenUsed.txt"
  "SJwt\\CMakeFiles\\SJwt_autogen.dir\\ParseCache.txt"
  "SJwt\\SJwt_autogen"
  "SWidget\\CMakeFiles\\SWidget_autogen.dir\\AutogenUsed.txt"
  "SWidget\\CMakeFiles\\SWidget_autogen.dir\\ParseCache.txt"
  "SWidget\\SWidget_autogen"
  "ThirdParty\\QXlsx\\CMakeFiles\\QXlsx_autogen.dir\\AutogenUsed.txt"
  "ThirdParty\\QXlsx\\CMakeFiles\\QXlsx_autogen.dir\\ParseCache.txt"
  "ThirdParty\\QXlsx\\QXlsx_autogen"
  "UPM-Client\\CMakeFiles\\UPM-Client_autogen.dir\\AutogenUsed.txt"
  "UPM-Client\\CMakeFiles\\UPM-Client_autogen.dir\\ParseCache.txt"
  "UPM-Client\\LoginRegister\\CMakeFiles\\LoginRegister_autogen.dir\\AutogenUsed.txt"
  "UPM-Client\\LoginRegister\\CMakeFiles\\LoginRegister_autogen.dir\\ParseCache.txt"
  "UPM-Client\\LoginRegister\\LoginRegister_autogen"
  "UPM-Client\\SubPage\\CMakeFiles\\SubPage_autogen.dir\\AutogenUsed.txt"
  "UPM-Client\\SubPage\\CMakeFiles\\SubPage_autogen.dir\\ParseCache.txt"
  "UPM-Client\\SubPage\\SubPage_autogen"
  "UPM-Client\\UPM-Client_autogen"
  "UPM-Server\\CMakeFiles\\UPM-Server_autogen.dir\\AutogenUsed.txt"
  "UPM-Server\\CMakeFiles\\UPM-Server_autogen.dir\\ParseCache.txt"
  "UPM-Server\\UPM-Server_autogen"
  "Util\\CMakeFiles\\Util_autogen.dir\\AutogenUsed.txt"
  "Util\\CMakeFiles\\Util_autogen.dir\\ParseCache.txt"
  "Util\\Util_autogen"
  )
endif()
