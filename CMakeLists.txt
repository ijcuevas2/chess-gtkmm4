cmake_minimum_required(VERSION 3.10)
project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Find glib-compile-resources
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources)
if (NOT GLIB_COMPILE_RESOURCES)
    message(FATAL_ERROR "Could not find glib-compile-resources")
endif ()

# Define variables for resource files
set(GRESOURCE_XML ${CMAKE_CURRENT_SOURCE_DIR}/chess.gresource.xml)
set(GRESOURCE_C ${CMAKE_BINARY_DIR}/chess_resources.c)
set(GRESOURCE_H ${CMAKE_BINARY_DIR}/chess_resources.h)

# Custom command to generate both .c and .h resource files
add_custom_command(
        OUTPUT ${GRESOURCE_C} ${GRESOURCE_H}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS
        --target=${GRESOURCE_C}
        --generate-source
        ${GRESOURCE_XML}
        COMMAND ${GLIB_COMPILE_RESOURCES}
        ARGS
        --target=${GRESOURCE_H}
        --generate-header
        ${GRESOURCE_XML}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${GRESOURCE_XML}
        COMMENT "Generating resource files"
)

# Custom target for resource compilation
add_custom_target(chess_resources DEPENDS ${GRESOURCE_C} ${GRESOURCE_H})

# Define source files
set(SOURCES
        main.cpp
        ${GRESOURCE_C}
        src/ChessPieces/King.cpp
        src/ChessPieces/Pawn.cpp
        src/ChessPieces/Bishop.cpp
        src/ChessPieces/Knight.cpp
        src/ChessPieces/Rook.cpp
        src/ChessPieces/Queen.cpp
        src/ChessPieces/ChessPiece.cpp
        src/ChessPieces/EmptyPiece.cpp
        src/Point2DPair/Point2DPair.cpp
        src/BoardSpace/BoardSpace.cpp
        src/HintMarker/HintMarker.cpp
        src/ChessWindow/ChessWindow.cpp
        src/ChessBoard/ChessBoardView.cpp
        src/ChessBoard/ChessBoardModel.cpp
        src/ChessImagesInfo/ChessImagesInfo.cpp
        src/ChessBoard/ChessBoardController.cpp
        src/FenModel/FenModel.cpp
        src/Utils/MathUtils.cpp
        src/Point2D/Point2D.cpp
        src/Utils/StringUtils.cpp
        src/Utils/FileUtils.cpp
        src/ChessMediator/ChessMediator.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add dependency on chess_resources
add_dependencies(${PROJECT_NAME} chess_resources)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_BINARY_DIR}
        ${GTKMM_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${GTKMM_LIBRARIES}
        ${GLIB_LIBRARIES}
        ${HARFBUZZ_LIBRARIES}
)

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
        ${GTKMM_CFLAGS_OTHER}
        ${GLIB_CFLAGS_OTHER}
        ${HARFBUZZ_CFLAGS_OTHER}
        $<$<CONFIG:Debug>:-g>
)

# Add library directories
target_link_directories(${PROJECT_NAME} PRIVATE
        ${GTKMM_LIBRARY_DIRS}
        ${GLIB_LIBRARY_DIRS}
        ${HARFBUZZ_LIBRARY_DIRS}
)
