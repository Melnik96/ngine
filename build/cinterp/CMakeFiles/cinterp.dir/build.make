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
include cinterp/CMakeFiles/cinterp.dir/depend.make

# Include the progress variables for this target.
include cinterp/CMakeFiles/cinterp.dir/progress.make

# Include the compile flags for this target's objects.
include cinterp/CMakeFiles/cinterp.dir/flags.make

cinterp/CMakeFiles/cinterp.dir/main.c.o: cinterp/CMakeFiles/cinterp.dir/flags.make
cinterp/CMakeFiles/cinterp.dir/main.c.o: ../cinterp/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/ngine/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cinterp/CMakeFiles/cinterp.dir/main.c.o"
	cd /home/melnik/projects/ngine/build/cinterp && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cinterp.dir/main.c.o   -c /home/melnik/projects/ngine/cinterp/main.c

cinterp/CMakeFiles/cinterp.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cinterp.dir/main.c.i"
	cd /home/melnik/projects/ngine/build/cinterp && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/ngine/cinterp/main.c > CMakeFiles/cinterp.dir/main.c.i

cinterp/CMakeFiles/cinterp.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cinterp.dir/main.c.s"
	cd /home/melnik/projects/ngine/build/cinterp && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/ngine/cinterp/main.c -o CMakeFiles/cinterp.dir/main.c.s

cinterp/CMakeFiles/cinterp.dir/main.c.o.requires:
.PHONY : cinterp/CMakeFiles/cinterp.dir/main.c.o.requires

cinterp/CMakeFiles/cinterp.dir/main.c.o.provides: cinterp/CMakeFiles/cinterp.dir/main.c.o.requires
	$(MAKE) -f cinterp/CMakeFiles/cinterp.dir/build.make cinterp/CMakeFiles/cinterp.dir/main.c.o.provides.build
.PHONY : cinterp/CMakeFiles/cinterp.dir/main.c.o.provides

cinterp/CMakeFiles/cinterp.dir/main.c.o.provides.build: cinterp/CMakeFiles/cinterp.dir/main.c.o

# Object files for target cinterp
cinterp_OBJECTS = \
"CMakeFiles/cinterp.dir/main.c.o"

# External object files for target cinterp
cinterp_EXTERNAL_OBJECTS =

../neditor/bin/cinterp: cinterp/CMakeFiles/cinterp.dir/main.c.o
../neditor/bin/cinterp: cinterp/CMakeFiles/cinterp.dir/build.make
../neditor/bin/cinterp: ../bin/lib/x86/libngine.so
../neditor/bin/cinterp: cinterp/CMakeFiles/cinterp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../../neditor/bin/cinterp"
	cd /home/melnik/projects/ngine/build/cinterp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cinterp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cinterp/CMakeFiles/cinterp.dir/build: ../neditor/bin/cinterp
.PHONY : cinterp/CMakeFiles/cinterp.dir/build

cinterp/CMakeFiles/cinterp.dir/requires: cinterp/CMakeFiles/cinterp.dir/main.c.o.requires
.PHONY : cinterp/CMakeFiles/cinterp.dir/requires

cinterp/CMakeFiles/cinterp.dir/clean:
	cd /home/melnik/projects/ngine/build/cinterp && $(CMAKE_COMMAND) -P CMakeFiles/cinterp.dir/cmake_clean.cmake
.PHONY : cinterp/CMakeFiles/cinterp.dir/clean

cinterp/CMakeFiles/cinterp.dir/depend:
	cd /home/melnik/projects/ngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melnik/projects/ngine /home/melnik/projects/ngine/cinterp /home/melnik/projects/ngine/build /home/melnik/projects/ngine/build/cinterp /home/melnik/projects/ngine/build/cinterp/CMakeFiles/cinterp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cinterp/CMakeFiles/cinterp.dir/depend

