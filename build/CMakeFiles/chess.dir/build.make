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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake -E rm -f

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
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating chess_resources.c"
	cd /Users/ismael/Documents/chess-gtkmm4 && /opt/homebrew/bin/glib-compile-resources --target=/Users/ismael/Documents/chess-gtkmm4/build/chess_resources.c --generate-source chess.gresource.xml

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

# Object files for target chess
chess_OBJECTS = \
"CMakeFiles/chess.dir/main.cpp.o" \
"CMakeFiles/chess.dir/chess_resources.c.o"

# External object files for target chess
chess_EXTERNAL_OBJECTS =

chess: CMakeFiles/chess.dir/main.cpp.o
chess: CMakeFiles/chess.dir/chess_resources.c.o
chess: CMakeFiles/chess.dir/build.make
chess: CMakeFiles/chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess.dir/build: chess
.PHONY : CMakeFiles/chess.dir/build

CMakeFiles/chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess.dir/clean

CMakeFiles/chess.dir/depend: chess_resources.c
	cd /Users/ismael/Documents/chess-gtkmm4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ismael/Documents/chess-gtkmm4 /Users/ismael/Documents/chess-gtkmm4 /Users/ismael/Documents/chess-gtkmm4/build /Users/ismael/Documents/chess-gtkmm4/build /Users/ismael/Documents/chess-gtkmm4/build/CMakeFiles/chess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/chess.dir/depend

