// PlatformLinuxWayland.h
#pragma once

#include "GameWindow.h"
#include "systems/VulkanInterface.h"
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <unordered_set>
#include <unordered_map>
#include <string>

class PlatformLinuxWayland : public GameWindow {
public:
    PlatformLinuxWayland(const std::string& title, int width, int height);
    ~PlatformLinuxWayland();

    void PollEvents() override;
    bool ShouldClose() const override;

    void* GetNativeWindowHandle() const override;
    void* GetNativeDisplayHandle() const override;
    std::string GetPlatformName() const override { return "Wayland"; }


    void clear() override;
    void refresh() override;

    VulkanRenderer& getRenderer() override { return renderer; }


    bool isKeyPressed(int keyCode) const override;
    bool isKeyPressed(const std::string& keyName) const override;

private:

    VulkanRenderer renderer;

    wl_display* display = nullptr;
    wl_surface* surface = nullptr;
    wl_registry* registry = nullptr;
    wl_compositor* compositor = nullptr;
    wl_seat* seat = nullptr;
    wl_keyboard* keyboard = nullptr;

    std::unordered_set<int> keysPressed;
    std::unordered_map<std::string, int> keyMap;

    bool shouldClose = false;

    void setupRegistry();

    static void handleGlobal(void* data, wl_registry* registry, uint32_t name,
                              const char* interface, uint32_t version);
    static void handleGlobalRemove(void* data, wl_registry* registry, uint32_t name);

    static void handleSeatCapabilities(void* data, wl_seat* seat, uint32_t capabilities);
    static void handleKey(void* data, wl_keyboard* keyboard, uint32_t serial,
                          uint32_t time, uint32_t key, uint32_t state);

    static const wl_registry_listener registryListener;
    static const wl_seat_listener seatListener;
    static const wl_keyboard_listener keyboardListener;
};
