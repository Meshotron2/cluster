# CMakeList.txt : CMake project for DWM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (App "app.c" "app.h" "../common/types.h" "../common/common.h")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    ADD_LIBRARY(math STATIC IMPORTED)
    target_link_libraries(App m)
 endif()
# TODO: Add tests and install targets if needed.
