cmake_minimum_required (VERSION 3.8)

#指定项目名称
project ("UPM-Client")

#设置自动moc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找指定模块
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql HttpServer Network)

#自动查找指定资源文件并存入一个变量中
file(GLOB UPM_SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB UPM_SERVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(PROJECT_SOURCES "Resource.qrc")

add_subdirectory(LoginRegister)
add_subdirectory(SubPage)

add_executable(${PROJECT_NAME} ${UPM_SERVER_SOURCES} ${UPM_SERVER_HEADERS} ${PROJECT_SOURCES})

#给目标连接库文件
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Sql Qt6::HttpServer Qt6::Network LoginRegister Util SWidget SubPage)
