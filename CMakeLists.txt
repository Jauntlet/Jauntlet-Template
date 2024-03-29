cmake_minimum_required(VERSION 3.10)

project(jauntlet)

# Set the directories for source code
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(JAUNTLET_DIR "${CMAKE_SOURCE_DIR}/Jauntlet")

# Get a list of all .cpp source files in the "src" directory
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")

# Get a list of all .cpp source files in the "Jauntlet" directory
file(GLOB_RECURSE JAUNTLET_FILES "${JAUNTLET_DIR}/*.cpp")

# Set the output directory for libraries
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/dependencies/lib")

# Include FreeType header directory
include_directories(/usr/include/freetype2)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(OPENGL REQUIRED gl)
pkg_check_modules(FREETYPE REQUIRED freetype2)

# Create a library from the "Jauntlet" source files
add_library(jauntlet ${JAUNTLET_FILES})

# Create an executable from the "src" source files
add_executable(game ${SRC_FILES})

# Set the C++ compiler to g++ on Unix
if (UNIX)
    set(CMAKE_CXX_COMPILER "g++")
endif()

# On all platforms, link the jauntlet library with our executable.
target_link_libraries(game PRIVATE jauntlet)

# Link game with its dependencies
target_link_libraries(game PRIVATE ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})

# Specify include directories for the "Jauntlet" directory (outside of it)
target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
