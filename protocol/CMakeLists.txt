project (libdeepstreamcpp-protocol)

set (PROJECT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file (GLOB_RECURSE PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories (${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries      (${PROJECT_NAME})