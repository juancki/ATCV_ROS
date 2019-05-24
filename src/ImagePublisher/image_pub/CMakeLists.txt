cmake_minimum_required(VERSION 2.8.3)
project(aruco)

find_package(catkin)

find_package(OpenCV 3 REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES aruco
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_library(# image_pub
  src/image_pub/main.cpp
)
target_link_libraries(# aruco
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(img_pub
  src/image_pub/main.cpp)
target_link_libraries(img_pub aruco ${catkin_LIBRARIES})

#############
## Install ##
#############

install(TARGETS image_pub img_pub
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY include/
   DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
)

