cmake_minimum_required(VERSION 3.10)
project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Find glib-compile-resources
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources)
if(NOT GLIB_COMPILE_RESOURCES)
    message(FATAL_ERROR "Could not find glib-compile-resources")
endif()

# Define a function to compile resources
function(glib_compile_resources output_var input_file)
    get_filename_component(input_file_name ${input_file} NAME_WE)
    set(output_file "${CMAKE_CURRENT_BINARY_DIR}/${input_file_name}_resources.c")
    add_custom_command(
        OUTPUT ${output_file}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS --target=${output_file} --generate-source ${input_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${input_file}
    )
    set(${output_var} ${output_file} PARENT_SCOPE)
endfunction()

# Compile the GResource file
glib_compile_resources(CHESS_RESOURCES chess.gresource.xml)

# Include directories
include_directories(${GTKMM_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})

# Add the executable
add_executable(${PROJECT_NAME} 
    main.cpp 
    ${CHESS_RESOURCES}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GLIB_LIBRARIES})

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER})


# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER})
