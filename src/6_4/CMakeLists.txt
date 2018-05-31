cmake_minimum_required(VERSION 3.11)

set(target_name LearnOpenCV_6_4)

project(${target_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${target_name} ${sources})
target_link_libraries(${target_name} ${OpenCV_LIBS})
set_target_properties(${target_name}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")