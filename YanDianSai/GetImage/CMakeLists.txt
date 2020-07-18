cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++0x")

project(getimage)

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Threads)
include_directories(${Threads_INCLUDE_DIRS})

link_libraries(/home/flk/桌面/yds/lib/libyds_lib.so)

include_directories(/home/flk/桌面/yds/lib/test)


#add_library(test_lib SHARED
#
#        )

#find_package(OpenCV REQUIRED)
add_executable(getimage main.cpp )
target_link_libraries(
        getimage
        ${OpenCV_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
)
