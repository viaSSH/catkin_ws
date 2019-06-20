cmake_minimum_required(VERSION 2.8.3)

project(mailbox)

 

## 캐킨 빌드를 할 때 요구되는 구성요소 패키지이다.

## 의존성 패키지로 message_generation, std_msgs, roscpp이며 

## 이 패키지들이 존재하지 않으면 빌드 도중에 에러가 난다.

find_package(catkin REQUIRED COMPONENTS

    message_generation

    roscpp
    
    std_msgs

)

 

## 메시지 선언: MsgTutorial.msg 

add_message_files(

    FILES 

    where.msg

)

 

## 의존하는 메시지를 설정하는 옵션이다.

## std_msgs가 설치되어 있지 않다면 빌드 도중에 에러가 난다.

generate_messages(

    DEPENDENCIES 

    std_msgs

)

 

## 캐킨 패키지 옵션으로 라이브러리, 캐킨 빌드 의존성, 시스템 의존 패키지를 기술한다.

catkin_package(  

    LIBRARIES mailbox

    CATKIN_DEPENDS roscpp std_msgs

)

 

## 인클루드 디렉터리를 설정한다.

include_directories(

    ${catkin_INCLUDE_DIRS}

)

## topic_publisher 노드에 대한 빌드 옵션이다. 

## 실행 파일, 타깃 링크 라이브러리, 추가 의존성 등을 설정한다.

add_executable(${PROJECT_NAME}_node src/mailbox_node.cpp) 
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} 
${catkin_EXPORTED_TARGETS}) 
target_link_libraries(${PROJECT_NAME}_node 
  ${catkin_LIBRARIES} 
  ${OpenCV_LIBS} 
) 

 

## topic_subscriber 노드에 대한 빌드 옵션이다. 

#add_executable(
#
#    topic_subscriber 
#
#    src/topic_subscriber.cpp
#
#)

#add_dependencies(

#    topic_subscriber 

#    ${${PROJECT_NAME}_EXPORTED_TARGETS} 

#    ${catkin_EXPORTED_TARGETS}

#)

#target_link_libraries(

#    topic_subscriber 

#    ${catkin_LIBRARIES}
#)
    


