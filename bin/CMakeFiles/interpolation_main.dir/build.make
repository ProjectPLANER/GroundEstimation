# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin"

# Include any dependencies generated for this target.
include CMakeFiles/interpolation_main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/interpolation_main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interpolation_main.dir/flags.make

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o: CMakeFiles/interpolation_main.dir/flags.make
CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o: /mnt/c/Users/Eek\ Ok\ 0987/Documents/CS\ Honour\ Proj.\ 2020/src/interpolateMain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o -c "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/interpolateMain.cpp"

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interpolation_main.dir/interpolateMain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/interpolateMain.cpp" > CMakeFiles/interpolation_main.dir/interpolateMain.cpp.i

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interpolation_main.dir/interpolateMain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/interpolateMain.cpp" -o CMakeFiles/interpolation_main.dir/interpolateMain.cpp.s

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.requires:

.PHONY : CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.requires

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.provides: CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.requires
	$(MAKE) -f CMakeFiles/interpolation_main.dir/build.make CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.provides.build
.PHONY : CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.provides

CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.provides.build: CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o


CMakeFiles/interpolation_main.dir/idwHandler.cpp.o: CMakeFiles/interpolation_main.dir/flags.make
CMakeFiles/interpolation_main.dir/idwHandler.cpp.o: /mnt/c/Users/Eek\ Ok\ 0987/Documents/CS\ Honour\ Proj.\ 2020/src/idwHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/interpolation_main.dir/idwHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interpolation_main.dir/idwHandler.cpp.o -c "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/idwHandler.cpp"

CMakeFiles/interpolation_main.dir/idwHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interpolation_main.dir/idwHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/idwHandler.cpp" > CMakeFiles/interpolation_main.dir/idwHandler.cpp.i

CMakeFiles/interpolation_main.dir/idwHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interpolation_main.dir/idwHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/idwHandler.cpp" -o CMakeFiles/interpolation_main.dir/idwHandler.cpp.s

CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.requires:

.PHONY : CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.requires

CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.provides: CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/interpolation_main.dir/build.make CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.provides.build
.PHONY : CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.provides

CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.provides.build: CMakeFiles/interpolation_main.dir/idwHandler.cpp.o


CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o: CMakeFiles/interpolation_main.dir/flags.make
CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o: /mnt/c/Users/Eek\ Ok\ 0987/Documents/CS\ Honour\ Proj.\ 2020/src/tiffHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o -c "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/tiffHandler.cpp"

CMakeFiles/interpolation_main.dir/tiffHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interpolation_main.dir/tiffHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/tiffHandler.cpp" > CMakeFiles/interpolation_main.dir/tiffHandler.cpp.i

CMakeFiles/interpolation_main.dir/tiffHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interpolation_main.dir/tiffHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/tiffHandler.cpp" -o CMakeFiles/interpolation_main.dir/tiffHandler.cpp.s

CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.requires:

.PHONY : CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.requires

CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.provides: CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/interpolation_main.dir/build.make CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.provides.build
.PHONY : CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.provides

CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.provides.build: CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o


CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o: CMakeFiles/interpolation_main.dir/flags.make
CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o: /mnt/c/Users/Eek\ Ok\ 0987/Documents/CS\ Honour\ Proj.\ 2020/src/krigeHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o -c "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/krigeHandler.cpp"

CMakeFiles/interpolation_main.dir/krigeHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interpolation_main.dir/krigeHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/krigeHandler.cpp" > CMakeFiles/interpolation_main.dir/krigeHandler.cpp.i

CMakeFiles/interpolation_main.dir/krigeHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interpolation_main.dir/krigeHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/krigeHandler.cpp" -o CMakeFiles/interpolation_main.dir/krigeHandler.cpp.s

CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.requires:

.PHONY : CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.requires

CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.provides: CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/interpolation_main.dir/build.make CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.provides.build
.PHONY : CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.provides

CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.provides.build: CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o


CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o: CMakeFiles/interpolation_main.dir/flags.make
CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o: /mnt/c/Users/Eek\ Ok\ 0987/Documents/CS\ Honour\ Proj.\ 2020/src/cvpHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o -c "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/cvpHandler.cpp"

CMakeFiles/interpolation_main.dir/cvpHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interpolation_main.dir/cvpHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/cvpHandler.cpp" > CMakeFiles/interpolation_main.dir/cvpHandler.cpp.i

CMakeFiles/interpolation_main.dir/cvpHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interpolation_main.dir/cvpHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src/cvpHandler.cpp" -o CMakeFiles/interpolation_main.dir/cvpHandler.cpp.s

CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.requires:

.PHONY : CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.requires

CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.provides: CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/interpolation_main.dir/build.make CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.provides.build
.PHONY : CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.provides

CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.provides.build: CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o


# Object files for target interpolation_main
interpolation_main_OBJECTS = \
"CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o" \
"CMakeFiles/interpolation_main.dir/idwHandler.cpp.o" \
"CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o" \
"CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o" \
"CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o"

# External object files for target interpolation_main
interpolation_main_EXTERNAL_OBJECTS =

interpolation_main: CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o
interpolation_main: CMakeFiles/interpolation_main.dir/idwHandler.cpp.o
interpolation_main: CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o
interpolation_main: CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o
interpolation_main: CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o
interpolation_main: CMakeFiles/interpolation_main.dir/build.make
interpolation_main: /usr/local/lib/libopencv_dnn.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_gapi.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_highgui.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_ml.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_objdetect.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_photo.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_stitching.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_video.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_videoio.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_imgcodecs.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_calib3d.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_features2d.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_flann.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_imgproc.so.4.2.0
interpolation_main: /usr/local/lib/libopencv_core.so.4.2.0
interpolation_main: CMakeFiles/interpolation_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable interpolation_main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interpolation_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interpolation_main.dir/build: interpolation_main

.PHONY : CMakeFiles/interpolation_main.dir/build

CMakeFiles/interpolation_main.dir/requires: CMakeFiles/interpolation_main.dir/interpolateMain.cpp.o.requires
CMakeFiles/interpolation_main.dir/requires: CMakeFiles/interpolation_main.dir/idwHandler.cpp.o.requires
CMakeFiles/interpolation_main.dir/requires: CMakeFiles/interpolation_main.dir/tiffHandler.cpp.o.requires
CMakeFiles/interpolation_main.dir/requires: CMakeFiles/interpolation_main.dir/krigeHandler.cpp.o.requires
CMakeFiles/interpolation_main.dir/requires: CMakeFiles/interpolation_main.dir/cvpHandler.cpp.o.requires

.PHONY : CMakeFiles/interpolation_main.dir/requires

CMakeFiles/interpolation_main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interpolation_main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interpolation_main.dir/clean

CMakeFiles/interpolation_main.dir/depend:
	cd "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src" "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/src" "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin" "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin" "/mnt/c/Users/Eek Ok 0987/Documents/CS Honour Proj. 2020/bin/CMakeFiles/interpolation_main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/interpolation_main.dir/depend

