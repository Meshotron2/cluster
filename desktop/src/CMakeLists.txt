# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(Task1)

# Add source to this project's executable.
add_executable (App "app.c" "types.h" "app.h")

ADD_LIBRARY(math STATIC IMPORTED)
target_link_libraries(App m)
# TODO: Add tests and install targets if needed.
