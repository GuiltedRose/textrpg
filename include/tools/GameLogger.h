#pragma once

#include <iostream>
#include <string>

class GameLogger {
public:
    static void info(const std::string& message);
    static void clear();

    // Vulkan hook for future debug overlays
    static void setOverlayCallback(void (*func)(const std::string&));

private:
    static void (*overlayCallback)(const std::string&);
};