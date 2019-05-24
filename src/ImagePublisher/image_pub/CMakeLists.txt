cmake_minimum_required(VERSION 2.8.3)
project(image_pub)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  sensor_msgs
)

find_package(catkin)

find_package(OpenCV 3 REQUIRED)

catkin_package(CATKIN_DEPENDS
   cv_bridge
   image_transport
   message_runtime
   sensor_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_library(image_pub
 src/image_pub/main.cpp
)

target_link_libraries(image_pub
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(img_pub
  src/image_pub/main.cpp)
add_dependencies(img_pub ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(img_pub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(img_sub
  src/image_pub/img_sub.cpp)
add_dependencies(img_sub ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(img_sub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

#############
## Install ##
#############

install(TARGETS img_pub
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
