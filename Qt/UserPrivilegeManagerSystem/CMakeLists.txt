cmake_minimum_required (VERSION 3.8)

#指定项目名称
project ("UserPrivilegeManagerSystem")

#Util工具模块
add_subdirectory(Util)
add_subdirectory(SWidget)
add_subdirectory(SJwt)

#Qxlsx模块
add_subdirectory(ThirdParty/Qxlsx)

#服务器
add_subdirectory(UPM-Server)

#客户端
add_subdirectory(UPM-Client)