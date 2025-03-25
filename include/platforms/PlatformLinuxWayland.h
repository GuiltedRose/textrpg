#pragma once

#include "GameWindow.h"
#include <string>
#include <wayland-client.h>

class PlatformLinuxWayland : public GameWindow {
public:
    PlatformLinuxWayland(const std::string& title, int width, int height);
    ~PlatformLinuxWayland() override;

    void PollEvents() override;
    bool ShouldClose() const override;

    void setupRegistry();

    void* GetNativeWindowHandle() const override;
    void* GetNativeDisplayHandle() const override;

    static void handleGlobal(void* data, wl_registry* registry, uint32_t name,
        const char* interface, uint32_t version);

    static void handleGlobalRemove(void* data, wl_registry* registry, uint32_t name);

    std::string GetPlatformName() const override { return "Wayland"; }

    // ✅ These two were missing:
    void clear() override;
    void refresh() override;

private:
    wl_display* display = nullptr;
    wl_surface* surface = nullptr;
    wl_registry* registry = nullptr;
    wl_compositor* compositor = nullptr;
    bool shouldClose = false;
};
