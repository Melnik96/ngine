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
include source/scenegraph/CMakeFiles/ngine_scenegraph.dir/depend.make

# Include the progress variables for this target.
include source/scenegraph/CMakeFiles/ngine_scenegraph.dir/progress.make

# Include the compile flags for this target's objects.
include source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o: ../source/scenegraph/material.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/material.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/material.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/material.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/material.c > CMakeFiles/ngine_scenegraph.dir/material.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/material.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/material.c -o CMakeFiles/ngine_scenegraph.dir/material.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o: ../source/scenegraph/entity.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/entity.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/entity.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/entity.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/entity.c > CMakeFiles/ngine_scenegraph.dir/entity.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/entity.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/entity.c -o CMakeFiles/ngine_scenegraph.dir/entity.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o: ../source/scenegraph/camera.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/camera.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/camera.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/camera.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/camera.c > CMakeFiles/ngine_scenegraph.dir/camera.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/camera.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/camera.c -o CMakeFiles/ngine_scenegraph.dir/camera.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o: ../source/scenegraph/texture.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/texture.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/texture.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/texture.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/texture.c > CMakeFiles/ngine_scenegraph.dir/texture.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/texture.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/texture.c -o CMakeFiles/ngine_scenegraph.dir/texture.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o: ../source/scenegraph/light.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/light.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/light.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/light.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/light.c > CMakeFiles/ngine_scenegraph.dir/light.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/light.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/light.c -o CMakeFiles/ngine_scenegraph.dir/light.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o: ../source/scenegraph/scene.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/scene.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/scene.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/scene.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/scene.c > CMakeFiles/ngine_scenegraph.dir/scene.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/scene.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/scene.c -o CMakeFiles/ngine_scenegraph.dir/scene.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o: ../source/scenegraph/trigger.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/trigger.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/trigger.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/trigger.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/trigger.c > CMakeFiles/ngine_scenegraph.dir/trigger.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/trigger.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/trigger.c -o CMakeFiles/ngine_scenegraph.dir/trigger.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o: ../source/scenegraph/sc_node.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/sc_node.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/sc_node.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/sc_node.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/sc_node.c > CMakeFiles/ngine_scenegraph.dir/sc_node.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/sc_node.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/sc_node.c -o CMakeFiles/ngine_scenegraph.dir/sc_node.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/flags.make
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o: ../source/scenegraph/ray.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_scenegraph.dir/ray.c.o   -c /home/melnik/projects/nutty/ngine/source/scenegraph/ray.c

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_scenegraph.dir/ray.c.i"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/source/scenegraph/ray.c > CMakeFiles/ngine_scenegraph.dir/ray.c.i

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_scenegraph.dir/ray.c.s"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/source/scenegraph/ray.c -o CMakeFiles/ngine_scenegraph.dir/ray.c.s

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.requires:
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.provides: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.requires
	$(MAKE) -f source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.provides.build
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.provides

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.provides.build: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o

# Object files for target ngine_scenegraph
ngine_scenegraph_OBJECTS = \
"CMakeFiles/ngine_scenegraph.dir/material.c.o" \
"CMakeFiles/ngine_scenegraph.dir/entity.c.o" \
"CMakeFiles/ngine_scenegraph.dir/camera.c.o" \
"CMakeFiles/ngine_scenegraph.dir/texture.c.o" \
"CMakeFiles/ngine_scenegraph.dir/light.c.o" \
"CMakeFiles/ngine_scenegraph.dir/scene.c.o" \
"CMakeFiles/ngine_scenegraph.dir/trigger.c.o" \
"CMakeFiles/ngine_scenegraph.dir/sc_node.c.o" \
"CMakeFiles/ngine_scenegraph.dir/ray.c.o"

# External object files for target ngine_scenegraph
ngine_scenegraph_EXTERNAL_OBJECTS =

../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build.make
../lib/x86/libngine_scenegraph.so: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../../lib/x86/libngine_scenegraph.so"
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ngine_scenegraph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build: ../lib/x86/libngine_scenegraph.so
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/build

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/material.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/entity.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/camera.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/texture.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/light.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/scene.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/trigger.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/sc_node.c.o.requires
source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires: source/scenegraph/CMakeFiles/ngine_scenegraph.dir/ray.c.o.requires
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/requires

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/clean:
	cd /home/melnik/projects/nutty/ngine/build/source/scenegraph && $(CMAKE_COMMAND) -P CMakeFiles/ngine_scenegraph.dir/cmake_clean.cmake
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/clean

source/scenegraph/CMakeFiles/ngine_scenegraph.dir/depend:
	cd /home/melnik/projects/nutty/ngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melnik/projects/nutty/ngine /home/melnik/projects/nutty/ngine/source/scenegraph /home/melnik/projects/nutty/ngine/build /home/melnik/projects/nutty/ngine/build/source/scenegraph /home/melnik/projects/nutty/ngine/build/source/scenegraph/CMakeFiles/ngine_scenegraph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/scenegraph/CMakeFiles/ngine_scenegraph.dir/depend
