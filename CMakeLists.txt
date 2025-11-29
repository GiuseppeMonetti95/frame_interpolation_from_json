cmake_minimum_required(VERSION 3.12)
project(frame_interpolation_from_json)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Eigen3 package
find_package(Eigen3 REQUIRED)

# Include directories
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(include)

# Add library
add_library(${PROJECT_NAME} src/FrameInterpolation.cpp)

# Add executable
add_executable(${PROJECT_NAME}_main src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)

target_link_libraries(${PROJECT_NAME}_main Eigen3::Eigen ${PROJECT_NAME})

# Set compiler flags for better optimization and debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")