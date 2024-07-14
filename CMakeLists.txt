cmake_minimum_required(VERSION 3.10)
project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Include directories
include_directories(${GTKMM_INCLUDE_DIRS})

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})