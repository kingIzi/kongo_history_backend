# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build

# Utility rule file for proto_tests_autogen.

# Include any custom commands dependencies for this target.
include backend_tests/CMakeFiles/proto_tests_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include backend_tests/CMakeFiles/proto_tests_autogen.dir/progress.make

backend_tests/CMakeFiles/proto_tests_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target proto_tests"
	cd /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/backend_tests && /usr/bin/cmake -E cmake_autogen /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/backend_tests/CMakeFiles/proto_tests_autogen.dir/AutogenInfo.json ""

proto_tests_autogen: backend_tests/CMakeFiles/proto_tests_autogen
proto_tests_autogen: backend_tests/CMakeFiles/proto_tests_autogen.dir/build.make
.PHONY : proto_tests_autogen

# Rule to build all files generated by this target.
backend_tests/CMakeFiles/proto_tests_autogen.dir/build: proto_tests_autogen
.PHONY : backend_tests/CMakeFiles/proto_tests_autogen.dir/build

backend_tests/CMakeFiles/proto_tests_autogen.dir/clean:
	cd /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/backend_tests && $(CMAKE_COMMAND) -P CMakeFiles/proto_tests_autogen.dir/cmake_clean.cmake
.PHONY : backend_tests/CMakeFiles/proto_tests_autogen.dir/clean

backend_tests/CMakeFiles/proto_tests_autogen.dir/depend:
	cd /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/backend_tests /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/backend_tests /home/coco/Documents/c++/projects/PERSONAL/kongo_history_backend/build/backend_tests/CMakeFiles/proto_tests_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : backend_tests/CMakeFiles/proto_tests_autogen.dir/depend

