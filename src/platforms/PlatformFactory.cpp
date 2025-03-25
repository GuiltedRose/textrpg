#include "PlatformFactory.h"
#include "GameWindow.h"

#ifdef _WIN32
#include "platforms/PlatformWindows.h"
#elif defined(__linux__)
#include "platforms/PlatformLinux.h"
#include "platforms/PlatformLinuxWayland.h"
#endif

#include <cstdlib>
#include <stdexcept>

std::unique_ptr<GameWindow> CreatePlatformWindow(const std::string& title, int width, int height) {
#ifdef _WIN32
    return std::make_unique<PlatformWindows>(title, width, height);

#elif defined(__linux__)
    if (std::getenv("WAYLAND_DISPLAY")) {
        try {
            return std::make_unique<PlatformLinuxWayland>(title, width, height);
        } catch (const std::exception& e) {
            if (std::getenv("DISPLAY")) {
                return std::make_unique<PlatformLinux>(title, width, height);
            } else {
                throw std::runtime_error(std::string("Wayland init failed: ") + e.what());
            }
        }
    } else if (std::getenv("DISPLAY")) {
        return std::make_unique<PlatformLinux>(title, width, height);
    } else {
        throw std::runtime_error("No supported display system found (Wayland or X11).");
    }
#else
    throw std::runtime_error("Unsupported platform.");
#endif
}
