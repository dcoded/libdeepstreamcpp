cmake_minimum_required (VERSION 3.0)

cmake_policy (SET CMP0042 NEW)
cmake_policy (SET CMP0002 OLD)

project (libdeepstreamcpp)

    set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    set (CMAKE_CXX_FLAGS "-std=c++1y -Wno-deprecated-declarations")
    set (CMAKE_BUILD_TYPE Debug)


    set (Boost_USE_STATIC_LIBS    OFF) 
    set (Boost_USE_MULTITHREADED  ON)  
    set (Boost_USE_STATIC_RUNTIME OFF) 
    find_package (Boost 1.59.0 COMPONENTS system thread REQUIRED) 


    set (PROJECT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
    set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

    # include_directories ("${PROJECT_BINARY_DIR}")
    include_directories ("${PROJECT_INCLUDE_DIR}")

    file (GLOB_RECURSE PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

    # add_library (${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
    add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})

    target_include_directories (${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
    target_link_libraries      (${PROJECT_NAME} ${Boost_LIBRARIES})