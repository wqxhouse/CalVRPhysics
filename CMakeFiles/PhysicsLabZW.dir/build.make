# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake28

# The command to remove a file.
RM = /usr/bin/cmake28 -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake28

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zowu/CVRPlugins

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zowu/CVRPlugins

# Include any dependencies generated for this target.
include calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/depend.make

# Include the progress variables for this target.
include calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/progress.make

# Include the compile flags for this target's objects.
include calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/flags.make

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/flags.make
calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o: calit2/PhysicsLabZW/PhysicsLabZW.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zowu/CVRPlugins/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o"
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o -c /home/zowu/CVRPlugins/calit2/PhysicsLabZW/PhysicsLabZW.cpp

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.i"
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zowu/CVRPlugins/calit2/PhysicsLabZW/PhysicsLabZW.cpp > CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.i

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.s"
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zowu/CVRPlugins/calit2/PhysicsLabZW/PhysicsLabZW.cpp -o CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.s

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.requires:
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.requires

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.provides: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.requires
	$(MAKE) -f calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/build.make calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.provides.build
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.provides

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.provides.build: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o

# Object files for target PhysicsLabZW
PhysicsLabZW_OBJECTS = \
"CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o"

# External object files for target PhysicsLabZW
PhysicsLabZW_EXTERNAL_OBJECTS =

/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/build.make
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgWidget.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgVolume.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgViewer.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgUtil.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgText.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgTerrain.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgSim.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgShadow.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgPresentation.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgParticle.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgManipulator.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgGA.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgFX.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgDB.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgAnimation.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libOpenThreads.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosg.so
/home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library /home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so"
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PhysicsLabZW.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/build: /home/calvr/CalVR/lib/calvr-plugins/libPhysicsLabZW.so
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/build

# Object files for target PhysicsLabZW
PhysicsLabZW_OBJECTS = \
"CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o"

# External object files for target PhysicsLabZW
PhysicsLabZW_EXTERNAL_OBJECTS =

calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/build.make
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgWidget.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgVolume.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgViewer.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgUtil.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgText.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgTerrain.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgSim.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgShadow.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgPresentation.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgParticle.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgManipulator.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgGA.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgFX.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgDB.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosgAnimation.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libOpenThreads.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: /home/calvr/CalVR/extern_libs/lib64/libosg.so
calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so"
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PhysicsLabZW.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/preinstall: calit2/PhysicsLabZW/CMakeFiles/CMakeRelink.dir/libPhysicsLabZW.so
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/preinstall

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/requires: calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/PhysicsLabZW.cpp.o.requires
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/requires

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/clean:
	cd /home/zowu/CVRPlugins/calit2/PhysicsLabZW && $(CMAKE_COMMAND) -P CMakeFiles/PhysicsLabZW.dir/cmake_clean.cmake
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/clean

calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/depend:
	cd /home/zowu/CVRPlugins && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zowu/CVRPlugins /home/zowu/CVRPlugins/calit2/PhysicsLabZW /home/zowu/CVRPlugins /home/zowu/CVRPlugins/calit2/PhysicsLabZW /home/zowu/CVRPlugins/calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : calit2/PhysicsLabZW/CMakeFiles/PhysicsLabZW.dir/depend
