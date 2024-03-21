cmake_minimum_required(VERSION 2.8)
project(imageBasics)
set(CMAKE_BUILD_TYPE "Debug" )
set(CMAKE_CXX_STANDARD 11)
# 寻找 OpenCV 库 
find_package( OpenCV REQUIRED )
# 添加头文件 
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( imageBasics imageBasics.cpp ) 
# 链接 OpenCV 库 
target_link_libraries( imageBasics ${OpenCV_LIBS})
