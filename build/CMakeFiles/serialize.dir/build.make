# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/melnik/projects/ngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/melnik/projects/ngine/build

# Include any dependencies generated for this target.
include CMakeFiles/serialize.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serialize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serialize.dir/flags.make

CMakeFiles/serialize.dir/examples/serialize/main.c.o: CMakeFiles/serialize.dir/flags.make
CMakeFiles/serialize.dir/examples/serialize/main.c.o: ../examples/serialize/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/ngine/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/serialize.dir/examples/serialize/main.c.o"
	/usr/lib/colorgcc/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/serialize.dir/examples/serialize/main.c.o   -c /home/melnik/projects/ngine/examples/serialize/main.c

CMakeFiles/serialize.dir/examples/serialize/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serialize.dir/examples/serialize/main.c.i"
	/usr/lib/colorgcc/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/ngine/examples/serialize/main.c > CMakeFiles/serialize.dir/examples/serialize/main.c.i

CMakeFiles/serialize.dir/examples/serialize/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serialize.dir/examples/serialize/main.c.s"
	/usr/lib/colorgcc/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/ngine/examples/serialize/main.c -o CMakeFiles/serialize.dir/examples/serialize/main.c.s

CMakeFiles/serialize.dir/examples/serialize/main.c.o.requires:
.PHONY : CMakeFiles/serialize.dir/examples/serialize/main.c.o.requires

CMakeFiles/serialize.dir/examples/serialize/main.c.o.provides: CMakeFiles/serialize.dir/examples/serialize/main.c.o.requires
	$(MAKE) -f CMakeFiles/serialize.dir/build.make CMakeFiles/serialize.dir/examples/serialize/main.c.o.provides.build
.PHONY : CMakeFiles/serialize.dir/examples/serialize/main.c.o.provides

CMakeFiles/serialize.dir/examples/serialize/main.c.o.provides.build: CMakeFiles/serialize.dir/examples/serialize/main.c.o

# Object files for target serialize
serialize_OBJECTS = \
"CMakeFiles/serialize.dir/examples/serialize/main.c.o"

# External object files for target serialize
serialize_EXTERNAL_OBJECTS =

../neditor/bin/serialize: CMakeFiles/serialize.dir/examples/serialize/main.c.o
../neditor/bin/serialize: CMakeFiles/serialize.dir/build.make
../neditor/bin/serialize: ../bin/lib/x86/libngine.so
../neditor/bin/serialize: /usr/lib/libBulletCollision.so
../neditor/bin/serialize: /usr/lib/libBulletDynamics.so
../neditor/bin/serialize: CMakeFiles/serialize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../neditor/bin/serialize"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serialize.dir/build: ../neditor/bin/serialize
.PHONY : CMakeFiles/serialize.dir/build

CMakeFiles/serialize.dir/requires: CMakeFiles/serialize.dir/examples/serialize/main.c.o.requires
.PHONY : CMakeFiles/serialize.dir/requires

CMakeFiles/serialize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serialize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serialize.dir/clean

CMakeFiles/serialize.dir/depend:
	cd /home/melnik/projects/ngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melnik/projects/ngine /home/melnik/projects/ngine /home/melnik/projects/ngine/build /home/melnik/projects/ngine/build /home/melnik/projects/ngine/build/CMakeFiles/serialize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serialize.dir/depend

