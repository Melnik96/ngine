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
include render/CMakeFiles/ngine_render.dir/depend.make

# Include the progress variables for this target.
include render/CMakeFiles/ngine_render.dir/progress.make

# Include the compile flags for this target's objects.
include render/CMakeFiles/ngine_render.dir/flags.make

render/CMakeFiles/ngine_render.dir/mesh.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/mesh.c.o: ../render/mesh.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/mesh.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/mesh.c.o   -c /home/melnik/projects/nutty/ngine/render/mesh.c

render/CMakeFiles/ngine_render.dir/mesh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/mesh.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/mesh.c > CMakeFiles/ngine_render.dir/mesh.c.i

render/CMakeFiles/ngine_render.dir/mesh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/mesh.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/mesh.c -o CMakeFiles/ngine_render.dir/mesh.c.s

render/CMakeFiles/ngine_render.dir/mesh.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/mesh.c.o.requires

render/CMakeFiles/ngine_render.dir/mesh.c.o.provides: render/CMakeFiles/ngine_render.dir/mesh.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/mesh.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/mesh.c.o.provides

render/CMakeFiles/ngine_render.dir/mesh.c.o.provides.build: render/CMakeFiles/ngine_render.dir/mesh.c.o

render/CMakeFiles/ngine_render.dir/render_target.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/render_target.c.o: ../render/render_target.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/render_target.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/render_target.c.o   -c /home/melnik/projects/nutty/ngine/render/render_target.c

render/CMakeFiles/ngine_render.dir/render_target.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/render_target.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/render_target.c > CMakeFiles/ngine_render.dir/render_target.c.i

render/CMakeFiles/ngine_render.dir/render_target.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/render_target.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/render_target.c -o CMakeFiles/ngine_render.dir/render_target.c.s

render/CMakeFiles/ngine_render.dir/render_target.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/render_target.c.o.requires

render/CMakeFiles/ngine_render.dir/render_target.c.o.provides: render/CMakeFiles/ngine_render.dir/render_target.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/render_target.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/render_target.c.o.provides

render/CMakeFiles/ngine_render.dir/render_target.c.o.provides.build: render/CMakeFiles/ngine_render.dir/render_target.c.o

render/CMakeFiles/ngine_render.dir/render.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/render.c.o: ../render/render.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/render.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/render.c.o   -c /home/melnik/projects/nutty/ngine/render/render.c

render/CMakeFiles/ngine_render.dir/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/render.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/render.c > CMakeFiles/ngine_render.dir/render.c.i

render/CMakeFiles/ngine_render.dir/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/render.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/render.c -o CMakeFiles/ngine_render.dir/render.c.s

render/CMakeFiles/ngine_render.dir/render.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/render.c.o.requires

render/CMakeFiles/ngine_render.dir/render.c.o.provides: render/CMakeFiles/ngine_render.dir/render.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/render.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/render.c.o.provides

render/CMakeFiles/ngine_render.dir/render.c.o.provides.build: render/CMakeFiles/ngine_render.dir/render.c.o

render/CMakeFiles/ngine_render.dir/technique.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/technique.c.o: ../render/technique.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/technique.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/technique.c.o   -c /home/melnik/projects/nutty/ngine/render/technique.c

render/CMakeFiles/ngine_render.dir/technique.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/technique.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/technique.c > CMakeFiles/ngine_render.dir/technique.c.i

render/CMakeFiles/ngine_render.dir/technique.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/technique.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/technique.c -o CMakeFiles/ngine_render.dir/technique.c.s

render/CMakeFiles/ngine_render.dir/technique.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/technique.c.o.requires

render/CMakeFiles/ngine_render.dir/technique.c.o.provides: render/CMakeFiles/ngine_render.dir/technique.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/technique.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/technique.c.o.provides

render/CMakeFiles/ngine_render.dir/technique.c.o.provides.build: render/CMakeFiles/ngine_render.dir/technique.c.o

render/CMakeFiles/ngine_render.dir/shader_prog.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/shader_prog.c.o: ../render/shader_prog.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/shader_prog.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/shader_prog.c.o   -c /home/melnik/projects/nutty/ngine/render/shader_prog.c

render/CMakeFiles/ngine_render.dir/shader_prog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/shader_prog.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/shader_prog.c > CMakeFiles/ngine_render.dir/shader_prog.c.i

render/CMakeFiles/ngine_render.dir/shader_prog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/shader_prog.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/shader_prog.c -o CMakeFiles/ngine_render.dir/shader_prog.c.s

render/CMakeFiles/ngine_render.dir/shader_prog.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/shader_prog.c.o.requires

render/CMakeFiles/ngine_render.dir/shader_prog.c.o.provides: render/CMakeFiles/ngine_render.dir/shader_prog.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/shader_prog.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/shader_prog.c.o.provides

render/CMakeFiles/ngine_render.dir/shader_prog.c.o.provides.build: render/CMakeFiles/ngine_render.dir/shader_prog.c.o

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o: render/CMakeFiles/ngine_render.dir/flags.make
render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o: ../render/techs/gl44_tech.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/melnik/projects/nutty/ngine/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o   -c /home/melnik/projects/nutty/ngine/render/techs/gl44_tech.c

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ngine_render.dir/techs/gl44_tech.c.i"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/melnik/projects/nutty/ngine/render/techs/gl44_tech.c > CMakeFiles/ngine_render.dir/techs/gl44_tech.c.i

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ngine_render.dir/techs/gl44_tech.c.s"
	cd /home/melnik/projects/nutty/ngine/build/render && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/melnik/projects/nutty/ngine/render/techs/gl44_tech.c -o CMakeFiles/ngine_render.dir/techs/gl44_tech.c.s

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.requires:
.PHONY : render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.requires

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.provides: render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.requires
	$(MAKE) -f render/CMakeFiles/ngine_render.dir/build.make render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.provides.build
.PHONY : render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.provides

render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.provides.build: render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o

# Object files for target ngine_render
ngine_render_OBJECTS = \
"CMakeFiles/ngine_render.dir/mesh.c.o" \
"CMakeFiles/ngine_render.dir/render_target.c.o" \
"CMakeFiles/ngine_render.dir/render.c.o" \
"CMakeFiles/ngine_render.dir/technique.c.o" \
"CMakeFiles/ngine_render.dir/shader_prog.c.o" \
"CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o"

# External object files for target ngine_render
ngine_render_EXTERNAL_OBJECTS =

../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/mesh.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/render_target.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/render.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/technique.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/shader_prog.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/build.make
../lib/x86/libngine_render.so: render/CMakeFiles/ngine_render.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../lib/x86/libngine_render.so"
	cd /home/melnik/projects/nutty/ngine/build/render && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ngine_render.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
render/CMakeFiles/ngine_render.dir/build: ../lib/x86/libngine_render.so
.PHONY : render/CMakeFiles/ngine_render.dir/build

render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/mesh.c.o.requires
render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/render_target.c.o.requires
render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/render.c.o.requires
render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/technique.c.o.requires
render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/shader_prog.c.o.requires
render/CMakeFiles/ngine_render.dir/requires: render/CMakeFiles/ngine_render.dir/techs/gl44_tech.c.o.requires
.PHONY : render/CMakeFiles/ngine_render.dir/requires

render/CMakeFiles/ngine_render.dir/clean:
	cd /home/melnik/projects/nutty/ngine/build/render && $(CMAKE_COMMAND) -P CMakeFiles/ngine_render.dir/cmake_clean.cmake
.PHONY : render/CMakeFiles/ngine_render.dir/clean

render/CMakeFiles/ngine_render.dir/depend:
	cd /home/melnik/projects/nutty/ngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melnik/projects/nutty/ngine /home/melnik/projects/nutty/ngine/render /home/melnik/projects/nutty/ngine/build /home/melnik/projects/nutty/ngine/build/render /home/melnik/projects/nutty/ngine/build/render/CMakeFiles/ngine_render.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : render/CMakeFiles/ngine_render.dir/depend

