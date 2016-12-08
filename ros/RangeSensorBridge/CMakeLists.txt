cmake_minimum_required(VERSION 2.8.3)
project(RangeSensorBridge)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs tf)

include(FindPkgConfig)
include(CheckIncludeFiles)
pkg_check_modules(cnoid_plugin REQUIRED choreonoid-body-plugin)
pkg_check_modules(openrtm_aist REQUIRED openrtm-aist)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES RangeSensorBridge
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

set(comp_name RangeSensorBridge)
set(comp_src src/RangeSensorRosBridge.cpp)

add_library(${comp_name} SHARED ${comp_src})
set_target_properties(RangeSensorBridge PROPERTIES PREFIX "")
target_link_libraries(RangeSensorBridge ${openrtm_aist_LIBRARY_DIRS})
target_link_libraries(RangeSensorBridge ${cnoid_plugin_LIBRARY_DIRS})
target_link_libraries(RangeSensorBridge ${catkin_LIBRARIES})

set(target ${comp_name} RangeSensorBridgeComp)
add_executable(RangeSensorBridgeComp src/RangeSensorRosBridgeComp.cpp ${comp_src})
target_link_libraries(RangeSensorBridgeComp ${openrtm_aist_LIBRARIES})
target_link_libraries(RangeSensorBridgeComp ${cnoid_plugin_LIBRARIES})
target_link_libraries(RangeSensorBridgeComp ${catkin_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#install(TARGETS RangeSensorBridgeComp DESTINATION ${CMAKE_PACKAGE_BIN_DESTINATION})
