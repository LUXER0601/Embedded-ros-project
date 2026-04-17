cmake_minimum_required(VERSION 2.8.3)
project(tp3_imu_control)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  turtlesim
  message_generation
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tp3_imu_control
#  CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Declare a cpp executable
add_executable(ControlTurtle src/ControlTurtle.cpp)

## Add cmake target dependencies of the executable/library
add_dependencies(ControlTurtle ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(ControlTurtle ${catkin_LIBRARIES})

#############
## Install ##
#############

# Mark executables for installation
# install(TARGETS ControlTurtle
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )
