# CMakeList.txt : CMake project for DWM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (room_partitioner "room_partitioner.c" "room_partitioner.h" "../common/types.h" "../common/common.h")
#get_filename_component(PARENT_DIR ../room_creator ABSOLUTE)
#include_directories(${PARENT_DIR}/src)

# TODO: Add tests and install targets if needed.
