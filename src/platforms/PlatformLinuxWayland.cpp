#include "PlatformLinuxWayland.h"
#include <stdexcept>
#include <cstring>

// Static listeners
const wl_registry_listener PlatformLinuxWayland::registryListener = {
    .global = PlatformLinuxWayland::handleGlobal,
    .global_remove = PlatformLinuxWayland::handleGlobalRemove
};

const wl_seat_listener PlatformLinuxWayland::seatListener = {
    .capabilities = PlatformLinuxWayland::handleSeatCapabilities,
    .name = nullptr
};

const wl_keyboard_listener PlatformLinuxWayland::keyboardListener = {
    .keymap = nullptr,
    .enter = nullptr,
    .leave = nullptr,
    .key = PlatformLinuxWayland::handleKey,
    .modifiers = nullptr,
    .repeat_info = nullptr
};

PlatformLinuxWayland::PlatformLinuxWayland(const std::string& title, int width, int height)
    : GameWindow(), renderer(GetNativeWindowHandle(), GetNativeDisplayHandle()){
    display = wl_display_connect(nullptr);
    if (!display) throw std::runtime_error("Failed to connect to Wayland display");

    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registryListener, this);
    wl_display_roundtrip(display);
    wl_display_roundtrip(display); // Ensure compositor + seat are set

    if (!compositor || !seat) throw std::runtime_error("Wayland compositor or seat not found");

    surface = wl_compositor_create_surface(compositor);
    if (!surface) throw std::runtime_error("Failed to create Wayland surface");

    // Setup key map (Linux input event codes)
    keyMap["w"] = 17;
    keyMap["a"] = 30;
    keyMap["s"] = 31;
    keyMap["d"] = 32;
    keyMap["up"] = 103;
    keyMap["down"] = 108;
    keyMap["left"] = 105;
    keyMap["right"] = 106;
    keyMap["enter"] = 28;
    keyMap["escape"] = 1;
}

PlatformLinuxWayland::~PlatformLinuxWayland() {
    if (keyboard) wl_keyboard_destroy(keyboard);
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
    return surface;
}

void* PlatformLinuxWayland::GetNativeDisplayHandle() const {
    return display;
}

void PlatformLinuxWayland::clear() {
    // Stub: rendering handled by Vulkan
}

void PlatformLinuxWayland::refresh() {
    // Stub: buffer commit by Vulkan
}

bool PlatformLinuxWayland::isKeyPressed(int keyCode) const {
    return keysPressed.find(keyCode) != keysPressed.end();
}

bool PlatformLinuxWayland::isKeyPressed(const std::string& keyName) const {
    auto it = keyMap.find(keyName);
    if (it == keyMap.end()) return false;
    return isKeyPressed(it->second);
}

// Registry handling
void PlatformLinuxWayland::handleGlobal(
    void* data, wl_registry* registry, uint32_t name,
    const char* interface, uint32_t version) {

    auto* self = static_cast<PlatformLinuxWayland*>(data);

    if (strcmp(interface, "wl_compositor") == 0) {
        self->compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface, 4));
    } else if (strcmp(interface, "wl_seat") == 0) {
        self->seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface, 7));
        wl_seat_add_listener(self->seat, &seatListener, self);
    }
}

void PlatformLinuxWayland::handleGlobalRemove(
    void* /*data*/, wl_registry* /*registry*/, uint32_t /*name*/) {
    // Not used
}

void PlatformLinuxWayland::handleSeatCapabilities(
    void* data, wl_seat* seat, uint32_t caps) {

    auto* self = static_cast<PlatformLinuxWayland*>(data);
    if (caps & WL_SEAT_CAPABILITY_KEYBOARD) {
        self->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(self->keyboard, &keyboardListener, self);
    }
}

void PlatformLinuxWayland::handleKey(
    void* data, wl_keyboard*, uint32_t, uint32_t, uint32_t key, uint32_t state) {

    auto* self = static_cast<PlatformLinuxWayland*>(data);

    if (state == WL_KEYBOARD_KEY_STATE_PRESSED) {
        self->keysPressed.insert(static_cast<int>(key));
    } else if (state == WL_KEYBOARD_KEY_STATE_RELEASED) {
        self->keysPressed.erase(static_cast<int>(key));
    }
}
