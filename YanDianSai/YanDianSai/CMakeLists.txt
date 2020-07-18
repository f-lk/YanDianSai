cmake_minimum_required(VERSION 2.8)

project(test)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(yds_lib SHARED
        ${PROJECT_SOURCE_DIR}/circle.cpp
        ${PROJECT_SOURCE_DIR}/src.cpp
        ${PROJECT_SOURCE_DIR}/stereoRectified.cpp
)

#版本信息
set_target_properties(yds_lib PROPERTIES VERSION 1.0 SOVERSION 1)

install(TARGETS yds_lib LIBRARY DESTINATION lib)

install(FILES circle.h src.h stereoRectified.h DESTINATION lib/${PROJECT_NAME})

#find_package(OpenCV REQUIRED)
add_executable(test main.cpp )
target_link_libraries(
        test
        ${OpenCV_LIBS}
        yds_lib
        )

