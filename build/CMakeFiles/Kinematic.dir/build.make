# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/java/Documents/kinematic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/java/Documents/kinematic/build

# Include any dependencies generated for this target.
include CMakeFiles/kinematic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/kinematic.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/kinematic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kinematic.dir/flags.make

CMakeFiles/kinematic.dir/codegen:
.PHONY : CMakeFiles/kinematic.dir/codegen

CMakeFiles/kinematic.dir/src/main.c.o: CMakeFiles/kinematic.dir/flags.make
CMakeFiles/kinematic.dir/src/main.c.o: /Users/java/Documents/kinematic/src/main.c
CMakeFiles/kinematic.dir/src/main.c.o: CMakeFiles/kinematic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/java/Documents/kinematic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/kinematic.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/kinematic.dir/src/main.c.o -MF CMakeFiles/kinematic.dir/src/main.c.o.d -o CMakeFiles/kinematic.dir/src/main.c.o -c /Users/java/Documents/kinematic/src/main.c

CMakeFiles/kinematic.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/kinematic.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/java/Documents/kinematic/src/main.c > CMakeFiles/kinematic.dir/src/main.c.i

CMakeFiles/kinematic.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/kinematic.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/java/Documents/kinematic/src/main.c -o CMakeFiles/kinematic.dir/src/main.c.s

# Object files for target kinematic
kinematic_OBJECTS = \
"CMakeFiles/kinematic.dir/src/main.c.o"

# External object files for target kinematic
kinematic_EXTERNAL_OBJECTS =

bin/kinematic: CMakeFiles/kinematic.dir/src/main.c.o
bin/kinematic: CMakeFiles/kinematic.dir/build.make
bin/kinematic: CMakeFiles/kinematic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/java/Documents/kinematic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/kinematic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kinematic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kinematic.dir/build: bin/kinematic
.PHONY : CMakeFiles/kinematic.dir/build

CMakeFiles/kinematic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kinematic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kinematic.dir/clean

CMakeFiles/kinematic.dir/depend:
	cd /Users/java/Documents/kinematic/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/java/Documents/kinematic /Users/java/Documents/kinematic /Users/java/Documents/kinematic/build /Users/java/Documents/kinematic/build /Users/java/Documents/kinematic/build/CMakeFiles/kinematic.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/kinematic.dir/depend

