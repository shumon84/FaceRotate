cmake_minimum_required(VERSION 2.8)

project(FaceRotate)

add_subdirectory(dlib-19.9/dlib dlib_build)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(FaceRotate
  main.cpp
  FacePose.cpp)
target_link_libraries(FaceRotate
  dlib::dlib
  ${OpenCV_LIBS})
