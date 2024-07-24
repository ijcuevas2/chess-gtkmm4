# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ismael/Documents/chess-gtkmm4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ismael/Documents/chess-gtkmm4/build

# Include any dependencies generated for this target.
include CMakeFiles/chess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess.dir/flags.make

chess_resources.c: /Users/ismael/Documents/chess-gtkmm4/chess.gresource.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating resource files"
	cd /Users/ismael/Documents/chess-gtkmm4 && /opt/homebrew/bin/glib-compile-resources --target=/Users/ismael/Documents/chess-gtkmm4/build/chess_resources.c --generate-source /Users/ismael/Documents/chess-gtkmm4/chess.gresource.xml
	cd /Users/ismael/Documents/chess-gtkmm4 && /opt/homebrew/bin/glib-compile-resources --target=/Users/ismael/Documents/chess-gtkmm4/build/chess_resources.h --generate-header /Users/ismael/Documents/chess-gtkmm4/chess.gresource.xml

chess_resources.h: chess_resources.c
	@$(CMAKE_COMMAND) -E touch_nocreate chess_resources.h

CMakeFiles/chess.dir/main.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/main.cpp.o: /Users/ismael/Documents/chess-gtkmm4/main.cpp
CMakeFiles/chess.dir/main.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chess.dir/main.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/main.cpp.o -MF CMakeFiles/chess.dir/main.cpp.o.d -o CMakeFiles/chess.dir/main.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/main.cpp

CMakeFiles/chess.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/main.cpp > CMakeFiles/chess.dir/main.cpp.i

CMakeFiles/chess.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/main.cpp -o CMakeFiles/chess.dir/main.cpp.s

CMakeFiles/chess.dir/chess_resources.c.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/chess_resources.c.o: chess_resources.c
CMakeFiles/chess.dir/chess_resources.c.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/chess.dir/chess_resources.c.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/chess.dir/chess_resources.c.o -MF CMakeFiles/chess.dir/chess_resources.c.o.d -o CMakeFiles/chess.dir/chess_resources.c.o -c /Users/ismael/Documents/chess-gtkmm4/build/chess_resources.c

CMakeFiles/chess.dir/chess_resources.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/chess.dir/chess_resources.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/build/chess_resources.c > CMakeFiles/chess.dir/chess_resources.c.i

CMakeFiles/chess.dir/chess_resources.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/chess.dir/chess_resources.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/build/chess_resources.c -o CMakeFiles/chess.dir/chess_resources.c.s

CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/King.cpp
CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/King.cpp

CMakeFiles/chess.dir/src/ChessPieces/King.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/King.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/King.cpp > CMakeFiles/chess.dir/src/ChessPieces/King.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/King.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/King.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/King.cpp -o CMakeFiles/chess.dir/src/ChessPieces/King.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Pawn.cpp
CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Pawn.cpp

CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Pawn.cpp > CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Pawn.cpp -o CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Bishop.cpp
CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Bishop.cpp

CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Bishop.cpp > CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Bishop.cpp -o CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Knight.cpp
CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Knight.cpp

CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Knight.cpp > CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Knight.cpp -o CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Rook.cpp
CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Rook.cpp

CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Rook.cpp > CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Rook.cpp -o CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Queen.cpp
CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Queen.cpp

CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Queen.cpp > CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/Queen.cpp -o CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/ChessPiece.cpp
CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/ChessPiece.cpp

CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/ChessPiece.cpp > CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/ChessPiece.cpp -o CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.s

CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/EmptyPiece.cpp
CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o -MF CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o.d -o CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/EmptyPiece.cpp

CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/EmptyPiece.cpp > CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.i

CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessPieces/EmptyPiece.cpp -o CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.s

CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/Coordinates/Coordinates.cpp
CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o -MF CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o.d -o CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/Coordinates/Coordinates.cpp

CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/Coordinates/Coordinates.cpp > CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.i

CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/Coordinates/Coordinates.cpp -o CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.s

CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/BoardSpace/BoardSpace.cpp
CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o -MF CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o.d -o CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/BoardSpace/BoardSpace.cpp

CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/BoardSpace/BoardSpace.cpp > CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.i

CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/BoardSpace/BoardSpace.cpp -o CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.s

CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/HintMarker/HintMarker.cpp
CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o -MF CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o.d -o CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/HintMarker/HintMarker.cpp

CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/HintMarker/HintMarker.cpp > CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.i

CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/HintMarker/HintMarker.cpp -o CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.s

CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessWindow/ChessWindow.cpp
CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o -MF CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o.d -o CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessWindow/ChessWindow.cpp

CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessWindow/ChessWindow.cpp > CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.i

CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessWindow/ChessWindow.cpp -o CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.s

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardView.cpp
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o -MF CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o.d -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardView.cpp

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardView.cpp > CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.i

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardView.cpp -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.s

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardModel.cpp
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o -MF CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o.d -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardModel.cpp

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardModel.cpp > CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.i

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardModel.cpp -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.s

CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessImagesInfo/ChessImagesInfo.cpp
CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o -MF CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o.d -o CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessImagesInfo/ChessImagesInfo.cpp

CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessImagesInfo/ChessImagesInfo.cpp > CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.i

CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessImagesInfo/ChessImagesInfo.cpp -o CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.s

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o: CMakeFiles/chess.dir/flags.make
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o: /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardController.cpp
CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o: CMakeFiles/chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o"
	ccache /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o -MF CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o.d -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o -c /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardController.cpp

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardController.cpp > CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.i

CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ismael/Documents/chess-gtkmm4/src/ChessBoard/ChessBoardController.cpp -o CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.s

# Object files for target chess
chess_OBJECTS = \
"CMakeFiles/chess.dir/main.cpp.o" \
"CMakeFiles/chess.dir/chess_resources.c.o" \
"CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o" \
"CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o" \
"CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o" \
"CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o" \
"CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o" \
"CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o" \
"CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o" \
"CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o" \
"CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o" \
"CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o"

# External object files for target chess
chess_EXTERNAL_OBJECTS =

chess: CMakeFiles/chess.dir/main.cpp.o
chess: CMakeFiles/chess.dir/chess_resources.c.o
chess: CMakeFiles/chess.dir/src/ChessPieces/King.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/Pawn.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/Bishop.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/Knight.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/Rook.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/Queen.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/ChessPiece.cpp.o
chess: CMakeFiles/chess.dir/src/ChessPieces/EmptyPiece.cpp.o
chess: CMakeFiles/chess.dir/src/Coordinates/Coordinates.cpp.o
chess: CMakeFiles/chess.dir/src/BoardSpace/BoardSpace.cpp.o
chess: CMakeFiles/chess.dir/src/HintMarker/HintMarker.cpp.o
chess: CMakeFiles/chess.dir/src/ChessWindow/ChessWindow.cpp.o
chess: CMakeFiles/chess.dir/src/ChessBoard/ChessBoardView.cpp.o
chess: CMakeFiles/chess.dir/src/ChessBoard/ChessBoardModel.cpp.o
chess: CMakeFiles/chess.dir/src/ChessImagesInfo/ChessImagesInfo.cpp.o
chess: CMakeFiles/chess.dir/src/ChessBoard/ChessBoardController.cpp.o
chess: CMakeFiles/chess.dir/build.make
chess: CMakeFiles/chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Linking CXX executable chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess.dir/build: chess
.PHONY : CMakeFiles/chess.dir/build

CMakeFiles/chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess.dir/clean

CMakeFiles/chess.dir/depend: chess_resources.c
CMakeFiles/chess.dir/depend: chess_resources.h
	cd /Users/ismael/Documents/chess-gtkmm4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ismael/Documents/chess-gtkmm4 /Users/ismael/Documents/chess-gtkmm4 /Users/ismael/Documents/chess-gtkmm4/build /Users/ismael/Documents/chess-gtkmm4/build /Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles/chess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/chess.dir/depend

