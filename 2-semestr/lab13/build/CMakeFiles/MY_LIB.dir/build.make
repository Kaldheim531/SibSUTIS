# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/piratik228/lab13

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piratik228/lab13/build

# Include any dependencies generated for this target.
include CMakeFiles/MY_LIB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MY_LIB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MY_LIB.dir/flags.make

CMakeFiles/MY_LIB.dir/functions.c.o: CMakeFiles/MY_LIB.dir/flags.make
CMakeFiles/MY_LIB.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/piratik228/lab13/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MY_LIB.dir/functions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MY_LIB.dir/functions.c.o   -c /home/piratik228/lab13/functions.c

CMakeFiles/MY_LIB.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MY_LIB.dir/functions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/piratik228/lab13/functions.c > CMakeFiles/MY_LIB.dir/functions.c.i

CMakeFiles/MY_LIB.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MY_LIB.dir/functions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/piratik228/lab13/functions.c -o CMakeFiles/MY_LIB.dir/functions.c.s

# Object files for target MY_LIB
MY_LIB_OBJECTS = \
"CMakeFiles/MY_LIB.dir/functions.c.o"

# External object files for target MY_LIB
MY_LIB_EXTERNAL_OBJECTS =

libMY_LIB.a: CMakeFiles/MY_LIB.dir/functions.c.o
libMY_LIB.a: CMakeFiles/MY_LIB.dir/build.make
libMY_LIB.a: CMakeFiles/MY_LIB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/piratik228/lab13/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libMY_LIB.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MY_LIB.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MY_LIB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MY_LIB.dir/build: libMY_LIB.a

.PHONY : CMakeFiles/MY_LIB.dir/build

CMakeFiles/MY_LIB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MY_LIB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MY_LIB.dir/clean

CMakeFiles/MY_LIB.dir/depend:
	cd /home/piratik228/lab13/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piratik228/lab13 /home/piratik228/lab13 /home/piratik228/lab13/build /home/piratik228/lab13/build /home/piratik228/lab13/build/CMakeFiles/MY_LIB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MY_LIB.dir/depend
