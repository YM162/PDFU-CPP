# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/yomismo/Projects/PDFU-CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yomismo/Projects/PDFU-CPP/build

# Include any dependencies generated for this target.
include CMakeFiles/PDFU-CPP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PDFU-CPP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PDFU-CPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PDFU-CPP.dir/flags.make

CMakeFiles/PDFU-CPP.dir/main.cpp.o: CMakeFiles/PDFU-CPP.dir/flags.make
CMakeFiles/PDFU-CPP.dir/main.cpp.o: ../main.cpp
CMakeFiles/PDFU-CPP.dir/main.cpp.o: CMakeFiles/PDFU-CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yomismo/Projects/PDFU-CPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PDFU-CPP.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PDFU-CPP.dir/main.cpp.o -MF CMakeFiles/PDFU-CPP.dir/main.cpp.o.d -o CMakeFiles/PDFU-CPP.dir/main.cpp.o -c /home/yomismo/Projects/PDFU-CPP/main.cpp

CMakeFiles/PDFU-CPP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PDFU-CPP.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yomismo/Projects/PDFU-CPP/main.cpp > CMakeFiles/PDFU-CPP.dir/main.cpp.i

CMakeFiles/PDFU-CPP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PDFU-CPP.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yomismo/Projects/PDFU-CPP/main.cpp -o CMakeFiles/PDFU-CPP.dir/main.cpp.s

# Object files for target PDFU-CPP
PDFU__CPP_OBJECTS = \
"CMakeFiles/PDFU-CPP.dir/main.cpp.o"

# External object files for target PDFU-CPP
PDFU__CPP_EXTERNAL_OBJECTS =

PDFU-CPP: CMakeFiles/PDFU-CPP.dir/main.cpp.o
PDFU-CPP: CMakeFiles/PDFU-CPP.dir/build.make
PDFU-CPP: /lib/libpodofo.so
PDFU-CPP: CMakeFiles/PDFU-CPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yomismo/Projects/PDFU-CPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PDFU-CPP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PDFU-CPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PDFU-CPP.dir/build: PDFU-CPP
.PHONY : CMakeFiles/PDFU-CPP.dir/build

CMakeFiles/PDFU-CPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PDFU-CPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PDFU-CPP.dir/clean

CMakeFiles/PDFU-CPP.dir/depend:
	cd /home/yomismo/Projects/PDFU-CPP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yomismo/Projects/PDFU-CPP /home/yomismo/Projects/PDFU-CPP /home/yomismo/Projects/PDFU-CPP/build /home/yomismo/Projects/PDFU-CPP/build /home/yomismo/Projects/PDFU-CPP/build/CMakeFiles/PDFU-CPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PDFU-CPP.dir/depend

