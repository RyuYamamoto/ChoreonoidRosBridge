cmake_minimum_required(VERSION 2.8.3)
project(JointStateBridge)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs tf)

include(FindPkgConfig)
include(CheckIncludeFiles)
pkg_check_modules(cnoid_plugin REQUIRED choreonoid-body-plugin)
pkg_check_modules(openrtm_aist REQUIRED openrtm-aist)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES JointStateBridge
  CATKIN_DEPENDS roscpp std_msgs tf
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${openrtm_aist_INCLUDE_DIRS}
  ${cnoid_plugin_INCLUDE_DIRS}
)

link_directories(
	${openrtm_aist_LIBRARY_DIRS}
	${cnoid_plugin_LIBRARY_DIRS}
	${CMAKE_MODULE_PATH}
)

set(comp_name JointStateBridge)
set(comp_src src/JointStateRosBridge.cpp)

add_library(${comp_name} SHARED ${comp_src})
set_target_properties(JointStateBridge PROPERTIES PREFIX "")
target_link_libraries(JointStateBridge ${openrtm_aist_LIBRARY_DIRS})
target_link_libraries(JointStateBridge ${cnoid_plugin_LIBRARY_DIRS})
target_link_libraries(JointStateBridge ${catkin_LIBRARIES})

set(target ${comp_name} JointStateBridgeComp)
add_executable(JointStateBridgeComp src/JointStateRosBridgeComp.cpp ${comp_src})
target_link_libraries(JointStateBridgeComp ${openrtm_aist_LIBRARIES})
target_link_libraries(JointStateBridgeComp ${cnoid_plugin_LIBRARIES})
target_link_libraries(JointStateBridgeComp ${catkin_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#install(TARGETS JointStateBridgeComp DESTINATION ${CMAKE_PACKAGE_BIN_DESTINATION})
