// PlatformWindowLinux.cpp
#include "platforms/PlatformLinux.h"

#ifdef HAVE_X11
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#ifdef HAVE_WAYLAND
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#endif

#include <cstdlib>
#include <iostream>

#ifdef HAVE_X11
static Window x11Window;
#endif

#ifdef HAVE_WAYLAND
static struct wl_display* wlDisplay = nullptr;
static struct wl_compositor* wlCompositor = nullptr;
static struct wl_surface* wlSurface = nullptr;
#endif

PlatformWindowLinux::PlatformWindowLinux() {
    const char* waylandEnv = std::getenv("WAYLAND_DISPLAY");
    const char* x11Env = std::getenv("DISPLAY");

#if defined(HAVE_WAYLAND) && defined(HAVE_X11)
    if (waylandEnv && !x11Env) {
        useWayland = true;
    } else if (x11Env && !waylandEnv) {
        useWayland = false;
    } else if (waylandEnv && x11Env) {
        // Default to Wayland if both are available
        useWayland = true;
    } else {
        std::cerr << "No supported display environment detected." << std::endl;
        exit(1);
    }
#elif defined(HAVE_WAYLAND)
    if (waylandEnv) {
        useWayland = true;
    } else {
        std::cerr << "Wayland display not available." << std::endl;
        exit(1);
    }
#elif defined(HAVE_X11)
    if (x11Env) {
        useWayland = false;
    } else {
        std::cerr << "X11 display not available." << std::endl;
        exit(1);
    }
#else
    std::cerr << "No windowing system compiled in." << std::endl;
    exit(1);
#endif

#ifdef HAVE_WAYLAND
    if (useWayland) {
        std::cout << "Wayland detected. Initializing Wayland backend...\n";
        wlDisplay = wl_display_connect(nullptr);
        if (!wlDisplay) {
            std::cerr << "Failed to connect to Wayland display." << std::endl;
            exit(1);
        }
        return;
    }
#endif

#ifdef HAVE_X11
    if (!useWayland) {
        std::cout << "X11 detected. Initializing X11 backend...\n";
        display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Failed to open X11 display" << std::endl;
            exit(1);
        }
        return;
    }
#endif

    std::cerr << "No supported display environment detected at runtime." << std::endl;
    exit(1);
}

PlatformWindowLinux::~PlatformWindowLinux() {
#ifdef HAVE_X11
    if (!useWayland && display) {
        XCloseDisplay(display);
    }
#endif
#ifdef HAVE_WAYLAND
    if (useWayland && wlDisplay) {
        wl_display_disconnect(wlDisplay);
        wlDisplay = nullptr;
    }
#endif
}

void PlatformWindowLinux::createWindow() {
#ifdef HAVE_WAYLAND
    if (useWayland) {
        std::cout << "[Wayland] Creating surface...\n";
        std::cout << "[Wayland] Surface created (stub)\n";
        return;
    }
#endif
#ifdef HAVE_X11
    if (!useWayland) {
        int screen = DefaultScreen(display);
        x11Window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                        100, 100, 800, 600, 1,
                                        BlackPixel(display, screen),
                                        WhitePixel(display, screen));

        XSelectInput(display, x11Window, ExposureMask | KeyPressMask);
        XMapWindow(display, x11Window);
        XFlush(display);
    }
#endif
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
#ifdef HAVE_WAYLAND
    if (useWayland && wlDisplay) {
        wl_display_flush(wlDisplay);
    }
#endif
#ifdef HAVE_X11
    if (!useWayland && display) {
        XFlush(display);
    }
#endif
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
