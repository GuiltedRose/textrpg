// PlatformWindowLinux.cpp
#include "platforms/PlatformLinux.h"
#include <X11/Xlib.h>
#include <wayland-client.h>
#include <cstdlib>
#include <iostream>

PlatformWindowLinux::PlatformWindowLinux() {
    const char* waylandEnv = std::getenv("WAYLAND_DISPLAY");
    const char* x11Env = std::getenv("DISPLAY");

    if (waylandEnv) {
        useWayland = true;
        std::cout << "Wayland detected. Initializing Wayland backend...\n";
        // Wayland init logic here
    } else if (x11Env) {
        useWayland = false;
        std::cout << "X11 detected. Initializing X11 backend...\n";
        display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Failed to open X11 display" << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "No supported display environment detected." << std::endl;
        exit(1);
    }
}

PlatformWindowLinux::~PlatformWindowLinux() {
    if (!useWayland && display) {
        XCloseDisplay(display);
    }
    // Add Wayland cleanup if needed
}

void PlatformWindowLinux::createWindow() {
    if (useWayland) {
        // Create Wayland window
    } else {
        // Create X11 window
    }
}

void PlatformWindowLinux::clear() {
    if (useWayland) {
        std::cout << "[Wayland] Clear screen\n";
    } else {
        std::cout << "[X11] Clear screen\n";
    }
}

void PlatformWindowLinux::drawText(const std::string& text) {
    if (useWayland) {
        std::cout << "[Wayland] " << text << std::endl;
    } else {
        std::cout << "[X11] " << text << std::endl;
    }
}

void PlatformWindowLinux::refresh() {
    // X11 or Wayland buffer swap if needed
}

void PlatformWindowLinux::setWriteMode(bool enabled) {
    writeMode = enabled;
}

char PlatformWindowLinux::waitForCharInput() {
    char ch;
    std::cin.get(ch);
    return ch;
}

std::string PlatformWindowLinux::waitForLineInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void PlatformWindowLinux::handleRawInput(char input) {
    std::cout << "[Raw Input] " << input << std::endl;
}

void PlatformWindowLinux::handleKeyPress(char input) {
    std::cout << "[Key Press] " << input << std::endl;
}

void PlatformWindowLinux::run() {
    drawText("PlatformWindowLinux running...");
    refresh();
}
