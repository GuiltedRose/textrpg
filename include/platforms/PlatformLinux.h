#pragma once

#include "GameWindow.h"
#include <string>

#ifdef HAVE_X11
#include <X11/Xlib.h>
#endif

#ifdef HAVE_WAYLAND
#include <wayland-client.h>
#endif

class PlatformWindowLinux : public GameWindow {
public:
    PlatformWindowLinux();
    ~PlatformWindowLinux() override;

    void createWindow() override;
    void clear() override;
    void drawText(const std::string& text) override;
    void refresh() override;
    void setWriteMode(bool enabled) override;
    char waitForCharInput() override;
    std::string waitForLineInput() override;

    void handleRawInput(char input);
    void handleKeyPress(char input);
    void run();

private:
    bool useWayland = false;
    bool writeMode = true;

#ifdef HAVE_X11
    Display* display = nullptr;
#endif

#ifdef HAVE_WAYLAND
    struct wl_display* wlDisplay = nullptr;
    struct wl_compositor* wlCompositor = nullptr;
    struct wl_surface* wlSurface = nullptr;
#endif
};