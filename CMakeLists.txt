# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 3.13.5)
# Set the name and the supported language of the project
project(roboGTK C)


# Put all libraries to one folder
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)


# Add an executable
add_subdirectory(src)

# Link the target to the GTK+ libraries
target_link_libraries(${PROJECT_NAME} PkgConfig::GTK3)
