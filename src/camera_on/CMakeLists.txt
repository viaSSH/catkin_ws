cmake_minimum_required(VERSION 2.8.3)
project(camera_on)
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  std_msgs
  message_generation
  
)

add_message_files(
  FILES
  where.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

catkin_package(   
  LIBRARIES camera_test2   
  CATKIN_DEPENDS cv_bridge roscpp std_msgs 
) 
 
include_directories(   
  ${catkin_INCLUDE_DIRS} 
) 
 
add_executable(${PROJECT_NAME}_node src/camera_on_node.cpp) 
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS}) 
target_link_libraries(${PROJECT_NAME}_node 
  ${catkin_LIBRARIES} 
  ${OpenCV_LIBS} 
) 
