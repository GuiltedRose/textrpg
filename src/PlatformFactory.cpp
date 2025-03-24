#include "PlatformFactory.h"

GameWindow* PlatformFactory::createGameWindow() {
#ifdef _WIN32
    return new PlatformWindowWindows();  // Create the Windows-specific platform window
#elif defined(__linux__)
    return new PlatformWindowLinux();    // Create the Linux-specific platform window
#elif defined(__APPLE__)
    return new PlatformWindowMac();      // Create the macOS-specific platform window
#else
    #error "Unsupported platform"
#endif
}