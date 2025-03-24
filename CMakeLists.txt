cmake_minimum_required(VERSION 3.10)

project(TextRPG VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/gameobjects
    ${CMAKE_SOURCE_DIR}/include/systems
    ${CMAKE_SOURCE_DIR}/include/platforms
)

# Platform-specific sources
if(WIN32)
    message(STATUS "Configuring for Windows")
    set(SOURCE_FILES
        src/platforms/PlatformWindows.cpp
        src/PlatformFactory.cpp
        src/input_utils.cpp
        src/main.cpp
        src/Game.cpp
        src/GameLogger.cpp
        src/GameWindow.cpp
        src/World.cpp
        src/MapTile.cpp
        src/gameobjects/Enemy.cpp
        src/gameobjects/Inventory.cpp
        src/gameobjects/Item.cpp
        src/gameobjects/Player.cpp
        src/systems/RivalSystem.cpp
        src/systems/CombatManager.cpp
    )
elseif(APPLE)
    message(STATUS "Configuring for macOS")
    enable_language(OBJCXX)  # Enable Objective-C++ support

    set(SOURCE_FILES
        src/platforms/PlatformWindowMac.mm
        src/PlatformFactory.cpp
        src/input_utils.cpp
        src/main.cpp
        src/Game.cpp
        src/GameLogger.cpp
        src/GameWindow.cpp
        src/World.cpp
        src/MapTile.cpp
        src/gameobjects/Enemy.cpp
        src/gameobjects/Inventory.cpp
        src/gameobjects/Item.cpp
        src/gameobjects/Player.cpp
        src/systems/RivalSystem.cpp
        src/systems/CombatManager.cpp
    )
else() # Assume Linux or other UNIX
    message(STATUS "Configuring for Linux/Unix")
    set(SOURCE_FILES
        src/platforms/PlatformLinux.cpp
        src/PlatformFactory.cpp
        src/input_utils.cpp
        src/main.cpp
        src/Game.cpp
        src/GameLogger.cpp
        src/GameWindow.cpp
        src/World.cpp
        src/MapTile.cpp
        src/gameobjects/Enemy.cpp
        src/gameobjects/Inventory.cpp
        src/gameobjects/Item.cpp
        src/gameobjects/Player.cpp
        src/systems/RivalSystem.cpp
        src/systems/CombatManager.cpp
    )
endif()

# Create executable
add_executable(TextRPG ${SOURCE_FILES})

# Link platform-specific libraries
if(WIN32)
    # Windows-specific libraries (e.g., User32.lib) could go here
elseif(APPLE)
    # Link macOS frameworks for Cocoa windowing
    target_link_libraries(TextRPG "-framework Cocoa")
elseif(UNIX)
    target_link_libraries(TextRPG X11)
endif()