 cmake_minimum_required( VERSION 2.8 )
 # 声明一个 cmake 工程
 project( useEigen )

 # 添加头文件 
include_directories( "/usr/include/eigen3" )
 add_executable(useEigen eigenMarix.cpp)
