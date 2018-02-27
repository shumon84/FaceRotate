cmake_minimum_required(VERSION 2.8)

project(FaceRotate)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(FaceRotate
  main.cpp
  Quaternion.cpp)
target_link_libraries(FaceRotate ${OpenCV_LIBS})
