#include "PlatformLinux.h"
#include <X11/Xlib.h>
#include <stdexcept>

PlatformLinux::PlatformLinux(const std::string& title, int width, int height) {
    display = XOpenDisplay(nullptr);
    if (!display) {
        throw std::runtime_error("Failed to open X display");
    }

    screen = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                 10, 10, width, height, 1,
                                 BlackPixel(display, screen),
                                 WhitePixel(display, screen));

    XStoreName(display, window, title.c_str());

    Atom deleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &deleteMessage, 1);

    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(display, window);
}

PlatformLinux::~PlatformLinux() {
    if (window)
        XDestroyWindow(display, window);
    if (display)
        XCloseDisplay(display);
}

void PlatformLinux::PollEvents() {
    while (XPending(display)) {
        XEvent event;
        XNextEvent(display, &event);
        if (event.type == ClientMessage || event.type == DestroyNotify) {
            shouldClose = true;
        }
    }
}

bool PlatformLinux::ShouldClose() const {
    return shouldClose;
}

void* PlatformLinux::GetNativeWindowHandle() const {
    return reinterpret_cast<void*>(window);
}

void* PlatformLinux::GetNativeDisplayHandle() const {
    return reinterpret_cast<void*>(display);
}

void PlatformLinux::clear() {
    // TODO: implement actual clearing
}

void PlatformLinux::refresh() {
    // TODO: implement actual refresh/flush
}