cmake_minimum_required(VERSION 3.10)
project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
if(NOT GTK4_FOUND)
    message(FATAL_ERROR "GTK4 not found. Please install GTK4 development files")
endif()
message(STATUS "Found GTK4 version: ${GTK4_VERSION}")
message(STATUS "GTK4 include dirs: ${GTK4_INCLUDE_DIRS}")

pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
if(NOT GLIB_FOUND)
    message(FATAL_ERROR "glib-2.0 not found. Please install glib development files")
endif()
message(STATUS "Found glib-2.0 version: ${GLIB_VERSION}")
message(STATUS "GLIB library dirs: ${GLIB_LIBRARY_DIRS}")
message(STATUS "GLIB libraries: ${GLIB_LIBRARIES}")

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
if(NOT GTKMM_FOUND)
    message(FATAL_ERROR "GTKMM4 not found. Please install GTKMM4 development files")
endif()

set(CMAKE_INSTALL_RPATH "${GLIB_LIBRARY_DIRS}")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)

enable_testing()
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        approvaltests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(approvaltests)

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources)
if (NOT GLIB_COMPILE_RESOURCES)
    message(FATAL_ERROR "Could not find glib-compile-resources")
endif ()

set(GRESOURCE_XML ${CMAKE_CURRENT_SOURCE_DIR}/chess.gresource.xml)
set(GRESOURCE_C ${CMAKE_BINARY_DIR}/chess_resources.c)
set(GRESOURCE_H ${CMAKE_BINARY_DIR}/chess_resources.h)

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

add_custom_target(chess_resources DEPENDS ${GRESOURCE_C} ${GRESOURCE_H})

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

add_library(chess_lib STATIC ${LIB_SOURCES})
add_dependencies(chess_lib chess_resources)

link_directories(
        ${GTK4_LIBRARY_DIRS}
        ${GTKMM_LIBRARY_DIRS}
        ${GLIB_LIBRARY_DIRS}
        ${HARFBUZZ_LIBRARY_DIRS}
)

target_include_directories(chess_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${CMAKE_BINARY_DIR}
        ${GTKMM_INCLUDE_DIRS}
        ${GTK4_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS}
)

target_link_libraries(chess_lib PUBLIC
        ${GTKMM_LIBRARIES}
        ${GTK4_LIBRARIES}
        ${GLIB_LIBRARIES}
        ${HARFBUZZ_LIBRARIES}
)

target_compile_options(chess_lib PRIVATE
        ${GTKMM_CFLAGS_OTHER}
        ${GTK4_CFLAGS_OTHER}
        ${GLIB_CFLAGS_OTHER}
        ${HARFBUZZ_CFLAGS_OTHER}
        $<$<CONFIG:Debug>:-g>
)

target_link_directories(chess_lib PUBLIC
        ${GTKMM_LIBRARY_DIRS}
        ${GTK4_LIBRARY_DIRS}
        ${GLIB_LIBRARY_DIRS}
        ${HARFBUZZ_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME}
        main.cpp
        ${GRESOURCE_C}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        chess_lib
        ${GTK4_LIBRARIES}
        ${GLIB_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "${GLIB_LIBRARY_DIRS};${GTK4_LIBRARY_DIRS}"
)

add_dependencies(${PROJECT_NAME} chess_resources)

add_executable(run_tests
        tests/sample_test.cpp
        tests/test_chess.h
)

target_include_directories(run_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${GTKMM_INCLUDE_DIRS}
        ${GTK4_INCLUDE_DIRS}
        ${GLIB_INCLUDE_DIRS}
        ${HARFBUZZ_INCLUDE_DIRS}
)

target_link_libraries(run_tests PRIVATE
        chess_lib
        GTest::gtest
        GTest::gtest_main
        ApprovalTests::ApprovalTests
)

add_test(NAME unit_tests COMMAND run_tests)
