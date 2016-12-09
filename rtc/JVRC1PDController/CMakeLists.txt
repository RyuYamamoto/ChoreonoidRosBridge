cmake_minimum_required(VERSION 2.8)

project(JVRC1PDController)

find_package(catkin REQUIRED)
find_package(Boost COMPONENTS system thread filesystem)

include(FindPkgConfig)
pkg_check_modules(cnoid_plugin REQUIRED choreonoid-body-plugin)
pkg_check_modules(openrtm_aist REQUIRED openrtm-aist)

include_directories(
	${openrtm_aist_INCLUDE_DIRS}
	${cnoid_plugin_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${openrtm_aist_LIBRARY_DIRS}
	${cnoid_plugin_LIBRARY_DIRS}
	${Boost_LIBRARY_DIRS}
)

catkin_package(
)

add_library(JVRC1PDController SHARED JVRC1PDController.cpp)
set_target_properties(JVRC1PDController PROPERTIES PREFIX "")

set(target JVRC1PDController)
target_link_libraries(JVRC1PDController
	${openrtm_aist_LIBRARIES}
	${cnoid_plugin_LIBRARIES}
	${Boost_LIBRARIES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

install(TARGETS JVRC1PDController LIBRARY DESTINATION /usr/lib/choreonoid-1.5/rtc)
install(FILES pdgain_jvrc1.txt DESTINATION /usr/lib/choreonoid-1.5/rtc)
