cmake_minimum_required (VERSION 3.0)

cmake_policy (SET CMP0042 NEW)
cmake_policy (SET CMP0002 OLD)

project (deepstreamcpp)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_CXX_FLAGS "-std=c++1y -Wno-deprecated-declarations")
set (CMAKE_BUILD_TYPE Debug)

add_subdirectory(transport)
# add_subdirectory(protocol)