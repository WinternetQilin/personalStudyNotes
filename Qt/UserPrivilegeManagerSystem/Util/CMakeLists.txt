cmake_minimum_required (VERSION 3.8)

#指定项目名称
project ("Util")

#设置自动moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找指定模块
find_package(Qt6 REQUIRED COMPONENTS Core Sql Network)

#自动查找指定资源文件并存入一个变量中
file(GLOB Util_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB Util_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(${PROJECT_NAME} STATIC ${Util_SOURCES} ${Util_HEADERS})

#将目标连接到库文件
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#给目标连接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Sql Qt6::Core Qt6::Network)
