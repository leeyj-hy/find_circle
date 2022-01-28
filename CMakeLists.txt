cmake_minimum_required(VERSION 3.0.2)
project(find_circle)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  cv_bridge
  usb_cam
)

find_package(OpenCV REQUIRED)


add_message_files(
  FILES
  Num.msg
)



generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS ${catkin_INCLUDE_DIRS}
  LIBRARIES find_circle 
  LIBRARIES opencv
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge
#  DEPENDS system_lib
)


include_directories(
  include ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


add_executable(circle_find src/circle_find.cpp)
target_link_libraries(circle_find ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(circle_find ${PROJECT_NAME}_generate_messages_cpp ${OpenCV_LIBRARIES})

add_executable(chord src/chord.cpp)
target_link_libraries(chord ${catkin_LIBRARIES})
add_dependencies(chord ${PROJECT_NAME}_generate_messages_cpp ${OpenCV_LIBRARIES})


