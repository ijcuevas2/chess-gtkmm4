cmake_minimum_required(VERSION 3.10)
project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Add debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
include_directories(${HARFBUZZ_INCLUDE_DIRS})
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

# Include directories
include_directories(
        ${GTKMM_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_BINARY_DIR}  # Include binary dir for generated files
)

# link_directories(${GTKMM_LIBRARY_DIRS})

# Add the executable
add_executable(${PROJECT_NAME}
        main.cpp
        ${GRESOURCE_C}
        src/ChessPieces/King.cpp
        headers/ChessPieces/King.h
        src/ChessPieces/Pawn.cpp
        headers/ChessPieces/Pawn.h
        src/ChessPieces/Bishop.cpp
        headers/ChessPieces/Bishop.h
        src/ChessPieces/Knight.cpp
        headers/ChessPieces/Knight.h
        src/ChessPieces/Rook.cpp
        headers/ChessPieces/Rook.h
        src/ChessPieces/Queen.cpp
        headers/ChessPieces/Queen.h
        src/ChessPieces/ChessPiece.cpp
        headers/ChessPieces/ChessPiece.h
        src/ChessPieces/EmptyPiece.cpp
        headers/ChessPieces/EmptyPiece.h
        src/Point2DPair/Point2DPair.cpp
        headers/Point2DPair/Point2DPair.h
        enum/Player.h
        enum/PieceType.h
        src/BoardSpace/BoardSpace.cpp
        headers/BoardSpace/BoardSpace.h
        src/HintMarker/HintMarker.cpp
        headers/HintMarker/HintMarker.h
        src/ChessWindow/ChessWindow.cpp
        headers/ChessWindow/ChessWindow.h
        src/ChessBoard/ChessBoardView.cpp
        headers/ChessBoard/ChessBoardView.h
        src/ChessBoard/ChessBoardModel.cpp
        headers/ChessBoard/ChessBoardModel.h
        src/ChessImagesInfo/ChessImagesInfo.cpp
        headers/ChessImagesInfo/ChessImagesInfo.h
        src/ChessBoard/ChessBoardController.cpp
        headers/ChessBoard/ChessBoardController.h
        headers/ChessBoardMediator/ChessBoardMediator.h
        src/ChessBoardMediator/ChessBoardMediator.cpp
        src/FenModel/FenModel.cpp
        headers/FenModel/FenModel.h
        src/MathUtils/MathUtils.cpp
        headers/MathUtils/MathUtils.h
        headers/Point2D/Point2D.h
        src/Point2D/Point2D.cpp
        src/ChessWindowMediator/ChessWindowMediator.cpp
        headers/ChessWindowMediator/ChessWindowMediator.h
)

# Add dependency on chess_resources
add_dependencies(${PROJECT_NAME} chess_resources)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GLIB_LIBRARIES})

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER})
