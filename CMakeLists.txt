cmake_minimum_required(VERSION 3.11)

# Require modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
# Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader PUBLIC "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/")
# No need for link_directories if we link directly

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## Tile Engine 
file(GLOB_RECURSE SOURCES TILEENGINE/*.cpp TILEENGINE/*.h)
add_executable(TILEENGINE ${SOURCES} "tileEngine/entity.cpp" "tileEngine/player.h" "tileEngine/player.cpp")
target_include_directories(TILEENGINE SYSTEM PRIVATE ${SFML_INCS})

# Link libraries to TILEENGINE
target_link_libraries(TILEENGINE lib_tile_level_loader lib_maths sfml-graphics)

# Set working directory for Visual Studio
set_target_properties(TILEENGINE 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

# Custom target to copy resources
add_custom_target(copy_tile_engine ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

add_dependencies(TILEENGINE copy_tile_engine)
