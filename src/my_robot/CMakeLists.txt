cmake_minimum_required(VERSION 3.0.2)
project(my_robot)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  gazebo_ros
  sensor_msgs
  message_generation
  urdf
  xacro
  nav_msgs
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  DriveToTarget.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs message_runtime 
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Add executables
add_executable(drive_bot src/drive_bot.cpp)
add_executable(process_image src/process_images.cpp)

## Add dependencies for your nodes
add_dependencies(drive_bot ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(process_image ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Link the executables to their respective libraries
target_link_libraries(drive_bot ${catkin_LIBRARIES})
target_link_libraries(process_image ${catkin_LIBRARIES})