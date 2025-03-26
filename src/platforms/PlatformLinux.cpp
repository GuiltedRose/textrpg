#include "PlatformLinux.h"
#include <stdexcept>

PlatformLinux::PlatformLinux(const std::string& title, int width, int height)
    : GameWindow(), renderer(GetNativeWindowHandle(), GetNativeDisplayHandle()) {
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

    keyMap["up"]    = XKeysymToKeycode(display, XK_Up);
    keyMap["down"]  = XKeysymToKeycode(display, XK_Down);
    keyMap["left"]  = XKeysymToKeycode(display, XK_Left);
    keyMap["right"] = XKeysymToKeycode(display, XK_Right);
    keyMap["enter"] = XKeysymToKeycode(display, XK_Return);
    keyMap["escape"] = XKeysymToKeycode(display, XK_Escape);
    keyMap["w"] = XKeysymToKeycode(display, XK_W);
    keyMap["a"] = XKeysymToKeycode(display, XK_A);
    keyMap["s"] = XKeysymToKeycode(display, XK_S);
    keyMap["d"] = XKeysymToKeycode(display, XK_D);
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

// Handling Keyboard Functions!
bool PlatformLinux::isKeyPressed(int keyCode) const {
    char key_return[32];
    XQueryKeymap(display, key_return);

    return key_return[keyCode / 8] & (1 << keyCode % 8);
}

bool PlatformLinux::isKeyPressed(const std::string& keyMap) const {
    return false;
}

void PlatformLinux::clear() {
    // TODO: implement actual clearing
}

void PlatformLinux::refresh() {
    // TODO: implement actual refresh/flush
}