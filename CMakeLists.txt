cmake_minimum_required(VERSION 3.10)
project(chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Find the required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# Enable testing
enable_testing()

# Include FetchContent for downloading test frameworks
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

# Fetch ApprovalTests
FetchContent_Declare(
        approvaltests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the frameworks available
FetchContent_MakeAvailable(googletest approvaltests)

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

# Define library source files (excluding main.cpp)
set(LIB_SOURCES
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

# Create the library
add_library(chess_lib STATIC ${LIB_SOURCES})

# Add dependency on chess_resources for the library
add_dependencies(chess_lib chess_resources)

# Set include directories for the library
target_include_directories(chess_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_BINARY_DIR}
        ${GTKMM_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS}
)

# Link libraries to chess_lib
target_link_libraries(chess_lib PUBLIC
        ${GTKMM_LIBRARIES}
        ${GLIB_LIBRARIES}
        ${HARFBUZZ_LIBRARIES}
)

# Set compiler flags for the library
target_compile_options(chess_lib PRIVATE
        ${GTKMM_CFLAGS_OTHER}
        ${GLIB_CFLAGS_OTHER}
        ${HARFBUZZ_CFLAGS_OTHER}
        $<$<CONFIG:Debug>:-g>
)

# Add library directories for the library
target_link_directories(chess_lib PUBLIC
        ${GTKMM_LIBRARY_DIRS}
        ${GLIB_LIBRARY_DIRS}
        ${HARFBUZZ_LIBRARY_DIRS}
)

# Add the main executable
add_executable(${PROJECT_NAME}
        main.cpp
        ${GRESOURCE_C}
)

# Link the main executable with the library
target_link_libraries(${PROJECT_NAME} PRIVATE chess_lib)

# Add dependency on chess_resources for the main executable
add_dependencies(${PROJECT_NAME} chess_resources)

# Add test executable
add_executable(run_tests
        tests/sample_test.cpp
        # Add other test files here
)

# Link the test executable with the library and test frameworks
target_link_libraries(run_tests PRIVATE
        chess_lib
        GTest::gtest
        GTest::gtest_main
        ApprovalTests::ApprovalTests
)

# Add the test to CTest
add_test(NAME unit_tests COMMAND run_tests)
