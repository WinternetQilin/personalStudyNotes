cmake_minimum_required (VERSION 3.8)

#指定项目名称
project ("UPM-Server")

#设置自动moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找指定模块
find_package(Qt6 REQUIRED Core Sql HttpServer)

#自动查找指定资源文件并存入一个变量中
file(GLOB UPM_SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB UPM_SERVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${PROJECT_NAME} ${UPM_SERVER_SOURCES} ${UPM_SERVER_HEADERS})

#给目标连接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt6::Sql Qt6::HttpServer Util SJwt)
