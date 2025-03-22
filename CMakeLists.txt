cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(TextRPG)

# Include directories
include_directories(include include/gameobjects include/systems)


# Specify source files for the executable
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/systems/RivalSystem.cpp
    src/gameobjects/Player.cpp
    src/gameobjects/Item.cpp
    src/gameobjects/Enemy.cpp
    # Other source files
)

# Define the executable target
add_executable(TextRPG ${SOURCES})

# Link the GameObjects library
target_link_libraries(TextRPG)

# Ensure include paths are accessible
target_include_directories(TextRPG PUBLIC include include/systems include/gameobjects)
