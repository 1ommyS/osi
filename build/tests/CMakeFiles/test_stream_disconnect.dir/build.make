# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /com.docker.devenvironments.code/zeromq-4.2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /com.docker.devenvironments.code/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_stream_disconnect.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_stream_disconnect.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_stream_disconnect.dir/flags.make

tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o: tests/CMakeFiles/test_stream_disconnect.dir/flags.make
tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o: /com.docker.devenvironments.code/zeromq-4.2.1/tests/test_stream_disconnect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/com.docker.devenvironments.code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o"
	cd /com.docker.devenvironments.code/build/tests && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o -c /com.docker.devenvironments.code/zeromq-4.2.1/tests/test_stream_disconnect.cpp

tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.i"
	cd /com.docker.devenvironments.code/build/tests && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /com.docker.devenvironments.code/zeromq-4.2.1/tests/test_stream_disconnect.cpp > CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.i

tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.s"
	cd /com.docker.devenvironments.code/build/tests && /usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /com.docker.devenvironments.code/zeromq-4.2.1/tests/test_stream_disconnect.cpp -o CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.s

# Object files for target test_stream_disconnect
test_stream_disconnect_OBJECTS = \
"CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o"

# External object files for target test_stream_disconnect
test_stream_disconnect_EXTERNAL_OBJECTS =

bin/test_stream_disconnect: tests/CMakeFiles/test_stream_disconnect.dir/test_stream_disconnect.cpp.o
bin/test_stream_disconnect: tests/CMakeFiles/test_stream_disconnect.dir/build.make
bin/test_stream_disconnect: lib/libzmq.so.4.2.1
bin/test_stream_disconnect: /usr/lib/aarch64-linux-gnu/librt.so
bin/test_stream_disconnect: /usr/lib/aarch64-linux-gnu/librt.so
bin/test_stream_disconnect: tests/CMakeFiles/test_stream_disconnect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/com.docker.devenvironments.code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/test_stream_disconnect"
	cd /com.docker.devenvironments.code/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_stream_disconnect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_stream_disconnect.dir/build: bin/test_stream_disconnect

.PHONY : tests/CMakeFiles/test_stream_disconnect.dir/build

tests/CMakeFiles/test_stream_disconnect.dir/clean:
	cd /com.docker.devenvironments.code/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_stream_disconnect.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_stream_disconnect.dir/clean

tests/CMakeFiles/test_stream_disconnect.dir/depend:
	cd /com.docker.devenvironments.code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /com.docker.devenvironments.code/zeromq-4.2.1 /com.docker.devenvironments.code/zeromq-4.2.1/tests /com.docker.devenvironments.code/build /com.docker.devenvironments.code/build/tests /com.docker.devenvironments.code/build/tests/CMakeFiles/test_stream_disconnect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_stream_disconnect.dir/depend

