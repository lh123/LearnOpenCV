cmake_minimum_required(VERSION 3.11)

project(LearnOpenCV)

set(CMAKE_BUILD_TYPE "Debug")

set(OpenCV_DIR "E:/VSCode/OpenCV-Lib/install/x64/mingw/lib")
find_package(OpenCV REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/5_2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/5_3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/5_4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/5_5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/5_6)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_2)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_3)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_5)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/6_7)