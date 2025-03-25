#include "platforms/PlatformLinuxWayland.h"
#include <stdexcept>
#include <iostream>

PlatformLinuxWayland::PlatformLinuxWayland(const std::string& title, int width, int height) {
    display = wl_display_connect(nullptr);
    if (!display) {
        throw std::runtime_error("Failed to connect to Wayland display");
    }

    registry = wl_display_get_registry(display);
    if (!registry) {
        throw std::runtime_error("Failed to get Wayland registry");
    }

    static const wl_registry_listener registryListener = {
        .global = handleGlobal,
        .global_remove = handleGlobalRemove
    };

    wl_registry_add_listener(registry, &registryListener, this);
    wl_display_roundtrip(display); // Block until we get compositor

    if (!compositor) {
        throw std::runtime_error("Failed to find Wayland compositor");
    }

    surface = wl_compositor_create_surface(compositor);
    if (!surface) {
        throw std::runtime_error("Failed to create Wayland surface");
    }
}

PlatformLinuxWayland::~PlatformLinuxWayland() {
    if (surface) wl_surface_destroy(surface);
    if (compositor) wl_compositor_destroy(compositor);
    if (registry) wl_registry_destroy(registry);
    if (display) wl_display_disconnect(display);
}

void PlatformLinuxWayland::PollEvents() {
    wl_display_dispatch_pending(display);
}

bool PlatformLinuxWayland::ShouldClose() const {
    return shouldClose;
}

void* PlatformLinuxWayland::GetNativeWindowHandle() const {
    return reinterpret_cast<void*>(surface);
}

void* PlatformLinuxWayland::GetNativeDisplayHandle() const {
    return reinterpret_cast<void*>(display);
}

void PlatformLinuxWayland::clear() {
    // Wayland-specific rendering clear logic would go here
    // For now, this is just a stub
}

void PlatformLinuxWayland::refresh() {
    // Wayland-specific buffer commit / refresh logic would go here
    // For now, this is just a stub
}

void PlatformLinuxWayland::setupRegistry() {
    // handled via listener
}

void PlatformLinuxWayland::handleGlobal(void* data, wl_registry* registry, uint32_t name,
                                         const char* interface, uint32_t version) {
    PlatformLinuxWayland* self = static_cast<PlatformLinuxWayland*>(data);
    if (std::string(interface) == "wl_compositor") {
        self->compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 1));
    }
}

void PlatformLinuxWayland::handleGlobalRemove(void* data, wl_registry* registry, uint32_t name) {
    // Not needed for now
}
