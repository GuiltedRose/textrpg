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

# Detect platform and set sources
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
    enable_language(OBJCXX)
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

elseif(UNIX)
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

# Now that sources are defined, create the executable
add_executable(TextRPG ${SOURCE_FILES})

# === Platform-specific linking AFTER target is created ===
if(WIN32)
    # Windows-specific libraries could be added here

elseif(APPLE)
    target_link_libraries(TextRPG "-framework Cocoa")

elseif(UNIX)
    find_package(X11)
    if(X11_FOUND)
        message(STATUS "X11 found, enabling HAVE_X11")
        target_compile_definitions(TextRPG PRIVATE HAVE_X11)
        target_include_directories(TextRPG PRIVATE ${X11_INCLUDE_DIR})
        target_link_libraries(TextRPG ${X11_LIBRARIES})
    else()
        message(WARNING "X11 not found. Building without X11 support.")
    endif()

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(WAYLAND_CLIENT wayland-client)
    if(WAYLAND_CLIENT_FOUND)
        message(STATUS "Wayland client found, enabling HAVE_WAYLAND")
        target_compile_definitions(TextRPG PRIVATE HAVE_WAYLAND)
        target_include_directories(TextRPG PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
        target_link_libraries(TextRPG ${WAYLAND_CLIENT_LIBRARIES})
    else()
        message(WARNING "Wayland client not found. Building without Wayland support.")
    endif()
endif()