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
CMAKE_SOURCE_DIR = /home/melnik/projects/nutty/ngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/melnik/projects/nutty/ngine/build

# Include any dependencies generated for this target.
include source/network/CMakeFiles/ngine_network.dir/depend.make

# Include the progress variables for this target.
include source/network/CMakeFiles/ngine_network.dir/progress.make

# Include the compile flags for this target's objects.
include source/network/CMakeFiles/ngine_network.dir/flags.make

source/network/CMakeFiles/ngine_network.dir/socket.c.o: source/network/CMakeFiles/ngine_network.dir/flags.make
source/network/CMakeFiles/ngine_network.dir/socket.c.o: ../source/network/socket.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/network/CMakeFiles/ngine_network.dir/socket.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_network.dir/socket.c.o   -c /home/melnik/projects/nutty/ngine/source/network/socket.c

source/network/CMakeFiles/ngine_network.dir/socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_network.dir/socket.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/network/socket.c > CMakeFiles/ngine_network.dir/socket.c.i

source/network/CMakeFiles/ngine_network.dir/socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_network.dir/socket.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/network/socket.c -o CMakeFiles/ngine_network.dir/socket.c.s

source/network/CMakeFiles/ngine_network.dir/socket.c.o.requires:
.PHONY : source/network/CMakeFiles/ngine_network.dir/socket.c.o.requires

source/network/CMakeFiles/ngine_network.dir/socket.c.o.provides: source/network/CMakeFiles/ngine_network.dir/socket.c.o.requires
	$(MAKE) -f source/network/CMakeFiles/ngine_network.dir/build.make source/network/CMakeFiles/ngine_network.dir/socket.c.o.provides.build
.PHONY : source/network/CMakeFiles/ngine_network.dir/socket.c.o.provides

source/network/CMakeFiles/ngine_network.dir/socket.c.o.provides.build: source/network/CMakeFiles/ngine_network.dir/socket.c.o

source/network/CMakeFiles/ngine_network.dir/server.c.o: source/network/CMakeFiles/ngine_network.dir/flags.make
source/network/CMakeFiles/ngine_network.dir/server.c.o: ../source/network/server.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/network/CMakeFiles/ngine_network.dir/server.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_network.dir/server.c.o   -c /home/melnik/projects/nutty/ngine/source/network/server.c

source/network/CMakeFiles/ngine_network.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_network.dir/server.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/network/server.c > CMakeFiles/ngine_network.dir/server.c.i

source/network/CMakeFiles/ngine_network.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_network.dir/server.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/network/server.c -o CMakeFiles/ngine_network.dir/server.c.s

source/network/CMakeFiles/ngine_network.dir/server.c.o.requires:
.PHONY : source/network/CMakeFiles/ngine_network.dir/server.c.o.requires

source/network/CMakeFiles/ngine_network.dir/server.c.o.provides: source/network/CMakeFiles/ngine_network.dir/server.c.o.requires
	$(MAKE) -f source/network/CMakeFiles/ngine_network.dir/build.make source/network/CMakeFiles/ngine_network.dir/server.c.o.provides.build
.PHONY : source/network/CMakeFiles/ngine_network.dir/server.c.o.provides

source/network/CMakeFiles/ngine_network.dir/server.c.o.provides.build: source/network/CMakeFiles/ngine_network.dir/server.c.o

source/network/CMakeFiles/ngine_network.dir/client.c.o: source/network/CMakeFiles/ngine_network.dir/flags.make
source/network/CMakeFiles/ngine_network.dir/client.c.o: ../source/network/client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/network/CMakeFiles/ngine_network.dir/client.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_network.dir/client.c.o   -c /home/melnik/projects/nutty/ngine/source/network/client.c

source/network/CMakeFiles/ngine_network.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_network.dir/client.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/network/client.c > CMakeFiles/ngine_network.dir/client.c.i

source/network/CMakeFiles/ngine_network.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_network.dir/client.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/network && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/network/client.c -o CMakeFiles/ngine_network.dir/client.c.s

source/network/CMakeFiles/ngine_network.dir/client.c.o.requires:
.PHONY : source/network/CMakeFiles/ngine_network.dir/client.c.o.requires

source/network/CMakeFiles/ngine_network.dir/client.c.o.provides: source/network/CMakeFiles/ngine_network.dir/client.c.o.requires
	$(MAKE) -f source/network/CMakeFiles/ngine_network.dir/build.make source/network/CMakeFiles/ngine_network.dir/client.c.o.provides.build
.PHONY : source/network/CMakeFiles/ngine_network.dir/client.c.o.provides

source/network/CMakeFiles/ngine_network.dir/client.c.o.provides.build: source/network/CMakeFiles/ngine_network.dir/client.c.o

# Object files for target ngine_network
ngine_network_OBJECTS = \
"CMakeFiles/ngine_network.dir/socket.c.o" \
"CMakeFiles/ngine_network.dir/server.c.o" \
"CMakeFiles/ngine_network.dir/client.c.o"

# External object files for target ngine_network
ngine_network_EXTERNAL_OBJECTS =

../lib/x86/libngine_network.so: source/network/CMakeFiles/ngine_network.dir/socket.c.o
../lib/x86/libngine_network.so: source/network/CMakeFiles/ngine_network.dir/server.c.o
../lib/x86/libngine_network.so: source/network/CMakeFiles/ngine_network.dir/client.c.o
../lib/x86/libngine_network.so: source/network/CMakeFiles/ngine_network.dir/build.make
../lib/x86/libngine_network.so: source/network/CMakeFiles/ngine_network.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../lib/x86/libngine_network.so"
	cd /home/melnik/projects/nutty/ngine/build/source/network && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ngine_network.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/network/CMakeFiles/ngine_network.dir/build: ../lib/x86/libngine_network.so
.PHONY : source/network/CMakeFiles/ngine_network.dir/build

source/network/CMakeFiles/ngine_network.dir/requires: source/network/CMakeFiles/ngine_network.dir/socket.c.o.requires
source/network/CMakeFiles/ngine_network.dir/requires: source/network/CMakeFiles/ngine_network.dir/server.c.o.requires
source/network/CMakeFiles/ngine_network.dir/requires: source/network/CMakeFiles/ngine_network.dir/client.c.o.requires
.PHONY : source/network/CMakeFiles/ngine_network.dir/requires

source/network/CMakeFiles/ngine_network.dir/clean:
	cd /home/melnik/projects/nutty/ngine/build/source/network && $(CMAKE_COMMAND) -P CMakeFiles/ngine_network.dir/cmake_clean.cmake
.PHONY : source/network/CMakeFiles/ngine_network.dir/clean

source/network/CMakeFiles/ngine_network.dir/depend:
	cd /home/melnik/projects/nutty/ngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melnik/projects/nutty/ngine /home/melnik/projects/nutty/ngine/source/network /home/melnik/projects/nutty/ngine/build /home/melnik/projects/nutty/ngine/build/source/network /home/melnik/projects/nutty/ngine/build/source/network/CMakeFiles/ngine_network.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/network/CMakeFiles/ngine_network.dir/depend

