# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\java\Documents\kinematic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\java\Documents\kinematic\build

# Include any dependencies generated for this target.
include CMakeFiles/YourProjectName.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/YourProjectName.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/YourProjectName.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/YourProjectName.dir/flags.make

CMakeFiles/YourProjectName.dir/codegen:
.PHONY : CMakeFiles/YourProjectName.dir/codegen

CMakeFiles/YourProjectName.dir/src/main.c.obj: CMakeFiles/YourProjectName.dir/flags.make
CMakeFiles/YourProjectName.dir/src/main.c.obj: CMakeFiles/YourProjectName.dir/includes_C.rsp
CMakeFiles/YourProjectName.dir/src/main.c.obj: C:/Users/java/Documents/kinematic/src/main.c
CMakeFiles/YourProjectName.dir/src/main.c.obj: CMakeFiles/YourProjectName.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\java\Documents\kinematic\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/YourProjectName.dir/src/main.c.obj"
	C:\PROGRA~1\MinGW\mingw\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/YourProjectName.dir/src/main.c.obj -MF CMakeFiles\YourProjectName.dir\src\main.c.obj.d -o CMakeFiles\YourProjectName.dir\src\main.c.obj -c C:\Users\java\Documents\kinematic\src\main.c

CMakeFiles/YourProjectName.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/YourProjectName.dir/src/main.c.i"
	C:\PROGRA~1\MinGW\mingw\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\java\Documents\kinematic\src\main.c > CMakeFiles\YourProjectName.dir\src\main.c.i

CMakeFiles/YourProjectName.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/YourProjectName.dir/src/main.c.s"
	C:\PROGRA~1\MinGW\mingw\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\java\Documents\kinematic\src\main.c -o CMakeFiles\YourProjectName.dir\src\main.c.s

# Object files for target YourProjectName
YourProjectName_OBJECTS = \
"CMakeFiles/YourProjectName.dir/src/main.c.obj"

# External object files for target YourProjectName
YourProjectName_EXTERNAL_OBJECTS =

YourProjectName.exe: CMakeFiles/YourProjectName.dir/src/main.c.obj
YourProjectName.exe: CMakeFiles/YourProjectName.dir/build.make
YourProjectName.exe: C:/Users/java/Documents/kinematic/lib/libSDL2.dll.a
YourProjectName.exe: C:/Users/java/Documents/kinematic/lib/libSDL2main.a
YourProjectName.exe: CMakeFiles/YourProjectName.dir/linkLibs.rsp
YourProjectName.exe: CMakeFiles/YourProjectName.dir/objects1.rsp
YourProjectName.exe: CMakeFiles/YourProjectName.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\java\Documents\kinematic\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable YourProjectName.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\YourProjectName.dir\link.txt --verbose=$(VERBOSE)
	"C:\Program Files\CMake\bin\cmake.exe" -E copy_if_different C:/Users/java/Documents/kinematic/lib/SDL2.dll C:/Users/java/Documents/kinematic/build

# Rule to build all files generated by this target.
CMakeFiles/YourProjectName.dir/build: YourProjectName.exe
.PHONY : CMakeFiles/YourProjectName.dir/build

CMakeFiles/YourProjectName.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\YourProjectName.dir\cmake_clean.cmake
.PHONY : CMakeFiles/YourProjectName.dir/clean

CMakeFiles/YourProjectName.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\java\Documents\kinematic C:\Users\java\Documents\kinematic C:\Users\java\Documents\kinematic\build C:\Users\java\Documents\kinematic\build C:\Users\java\Documents\kinematic\build\CMakeFiles\YourProjectName.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/YourProjectName.dir/depend

