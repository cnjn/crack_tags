# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.11

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\cracl\libnfc-1.7.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\cracl\build

# Include any dependencies generated for this target.
include utils/CMakeFiles/nfc-emulate-forum-tag4.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/nfc-emulate-forum-tag4.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/nfc-emulate-forum-tag4.dir/flags.make

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/flags.make
utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/includes_C.rsp
utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj: F:/cracl/libnfc-1.7.1/utils/nfc-emulate-forum-tag4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\cracl\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj"
	cd /d F:\cracl\build\utils && C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\nfc-emulate-forum-tag4.dir\nfc-emulate-forum-tag4.c.obj   -c F:\cracl\libnfc-1.7.1\utils\nfc-emulate-forum-tag4.c

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.i"
	cd /d F:\cracl\build\utils && C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E F:\cracl\libnfc-1.7.1\utils\nfc-emulate-forum-tag4.c > CMakeFiles\nfc-emulate-forum-tag4.dir\nfc-emulate-forum-tag4.c.i

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.s"
	cd /d F:\cracl\build\utils && C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S F:\cracl\libnfc-1.7.1\utils\nfc-emulate-forum-tag4.c -o CMakeFiles\nfc-emulate-forum-tag4.dir\nfc-emulate-forum-tag4.c.s

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/__/windows/nfc-emulate-forum-tag4.rc.obj: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/flags.make
utils/CMakeFiles/nfc-emulate-forum-tag4.dir/__/windows/nfc-emulate-forum-tag4.rc.obj: windows/nfc-emulate-forum-tag4.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\cracl\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object utils/CMakeFiles/nfc-emulate-forum-tag4.dir/__/windows/nfc-emulate-forum-tag4.rc.obj"
	cd /d F:\cracl\build\utils && C:\TDM-GCC-64\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) F:\cracl\build\windows\nfc-emulate-forum-tag4.rc CMakeFiles\nfc-emulate-forum-tag4.dir\__\windows\nfc-emulate-forum-tag4.rc.obj

# Object files for target nfc-emulate-forum-tag4
nfc__emulate__forum__tag4_OBJECTS = \
"CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj" \
"CMakeFiles/nfc-emulate-forum-tag4.dir/__/windows/nfc-emulate-forum-tag4.rc.obj"

# External object files for target nfc-emulate-forum-tag4
nfc__emulate__forum__tag4_EXTERNAL_OBJECTS =

utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/nfc-emulate-forum-tag4.c.obj
utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/__/windows/nfc-emulate-forum-tag4.rc.obj
utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/build.make
utils/nfc-emulate-forum-tag4.exe: utils/libnfcutils.a
utils/nfc-emulate-forum-tag4.exe: libnfc/libnfc.dll.a
utils/nfc-emulate-forum-tag4.exe: F:/cracl/libusb-win32-bin-1.2.6.0/lib/gcc/libusb.a
utils/nfc-emulate-forum-tag4.exe: F:/cracl/pcre-7.0-bin/lib/libpcre.dll.a
utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/linklibs.rsp
utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/objects1.rsp
utils/nfc-emulate-forum-tag4.exe: utils/CMakeFiles/nfc-emulate-forum-tag4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\cracl\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable nfc-emulate-forum-tag4.exe"
	cd /d F:\cracl\build\utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\nfc-emulate-forum-tag4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/nfc-emulate-forum-tag4.dir/build: utils/nfc-emulate-forum-tag4.exe

.PHONY : utils/CMakeFiles/nfc-emulate-forum-tag4.dir/build

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/clean:
	cd /d F:\cracl\build\utils && $(CMAKE_COMMAND) -P CMakeFiles\nfc-emulate-forum-tag4.dir\cmake_clean.cmake
.PHONY : utils/CMakeFiles/nfc-emulate-forum-tag4.dir/clean

utils/CMakeFiles/nfc-emulate-forum-tag4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\cracl\libnfc-1.7.1 F:\cracl\libnfc-1.7.1\utils F:\cracl\build F:\cracl\build\utils F:\cracl\build\utils\CMakeFiles\nfc-emulate-forum-tag4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/nfc-emulate-forum-tag4.dir/depend

