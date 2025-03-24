#ifndef PLATFORM_FACTORY_H
#define PLATFORM_FACTORY_H

#ifdef _WIN32
    #include "PlatformWindows.h"
#elif defined(__linux__)
    #include "PlatformLinux.h"
#elif defined(__APPLE__)
    #include "PlatformMac.h"  // Add this line
#else
    #error "Unsupported platform"
#endif

class PlatformFactory {
public:
    static GameWindow* createGameWindow();
};

#endif