cmake_minimum_required(VERSION 3.10)
project(TextRPG VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# === Include Paths ===
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/gameobjects
    ${CMAKE_SOURCE_DIR}/include/systems
    ${CMAKE_SOURCE_DIR}/include/platforms
    ${CMAKE_SOURCE_DIR}/include/tools
)

# === Common Source Files ===
set(COMMON_SOURCES
    src/main.cpp
    src/Game.cpp
    src/platforms/PlatformFactory.cpp
    src/tools/GameLogger.cpp
    src/tools/font8x8.cpp
    src/tools/TextRenderer.cpp
    src/systems/VulkanInterface.cpp
    src/systems/CombatManager.cpp
    src/systems/RivalSystem.cpp
    src/gameobjects/World.cpp
    src/gameobjects/MapTile.cpp
    src/gameobjects/Enemy.cpp
    src/gameobjects/Inventory.cpp
    src/gameobjects/Item.cpp
    src/gameobjects/Player.cpp
)

# === Platform-specific Sources ===
set(PLATFORM_SOURCES "")
set(EXTRA_LIBS "")

if(WIN32)
    message(STATUS "Configuring for Windows")
    list(APPEND PLATFORM_SOURCES src/platforms/PlatformWindows.cpp)

elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")

    # X11 Support
    find_package(X11)
    if(X11_FOUND)
        message(STATUS "X11 found, enabling HAVE_X11")
        list(APPEND PLATFORM_SOURCES src/platforms/PlatformLinux.cpp)
        list(APPEND EXTRA_LIBS ${X11_LIBRARIES})
        set(HAVE_X11_COMPILE_DEF TRUE)
        set(X11_INCLUDE_DIRS ${X11_INCLUDE_DIR})  # Save for later include
    else()
        message(WARNING "X11 not found. Building without X11 support.")
    endif()

    # Wayland Support
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(WAYLAND_CLIENT wayland-client)
    if(WAYLAND_CLIENT_FOUND)
        message(STATUS "Wayland client found, enabling HAVE_WAYLAND")
        list(APPEND PLATFORM_SOURCES src/platforms/PlatformLinuxWayland.cpp)
        list(APPEND EXTRA_LIBS ${WAYLAND_CLIENT_LIBRARIES})
        set(HAVE_WAYLAND_COMPILE_DEF TRUE)
    else()
        message(WARNING "Wayland client not found. Building without Wayland support.")
    endif()
endif()

# === Vulkan Support ===
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan found: ${Vulkan_INCLUDE_DIRS}")
    include_directories(${Vulkan_INCLUDE_DIRS})
    list(APPEND EXTRA_LIBS ${Vulkan_LIBRARIES})
else()
    message(FATAL_ERROR "Vulkan not found. Please install the Vulkan SDK.")
endif()

# === Create Executable ===
add_executable(TextRPG ${COMMON_SOURCES} ${PLATFORM_SOURCES})

# === Platform-specific Definitions (after target is created) ===
if(UNIX)
    if(HAVE_X11_COMPILE_DEF)
        target_compile_definitions(TextRPG PRIVATE HAVE_X11)
        target_include_directories(TextRPG PRIVATE ${X11_INCLUDE_DIRS})
    endif()

    if(HAVE_WAYLAND_COMPILE_DEF)
        target_compile_definitions(TextRPG PRIVATE HAVE_WAYLAND)
        target_include_directories(TextRPG PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
    endif()
endif()

# === Link Libraries ===
if(EXTRA_LIBS)
    target_link_libraries(TextRPG ${EXTRA_LIBS})
endif()
