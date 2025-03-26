#include "systems/VulkanInterface.h"
#include "tools/stb_image_raw.h"

#ifdef _WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
    #include <windows.h>
    #include <vulkan/vulkan_win32.h>
#elif defined(HAVE_WAYLAND)
    #define VK_USE_PLATFORM_WAYLAND_KHR
    #include <wayland-client.h>
    #include <vulkan/vulkan_wayland.h>
#else
    #define VK_USE_PLATFORM_XLIB_KHR
    #include <X11/Xlib.h>
    #include <vulkan/vulkan_xlib.h>
#endif

#include <stdexcept>
#include <iostream>
#include <cstring> // for memcpy

VulkanRenderer::VulkanRenderer(void* window, void* display)
    : nativeWindow(window), nativeDisplay(display) {
    initVulkan();
    selectPhysicalDevice();
    loadFontTexture();
}

VulkanRenderer::~VulkanRenderer() {
    cleanup();
}

void VulkanRenderer::initVulkan() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "TextRPG";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "CustomEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

#ifdef _WIN32
    const char* extensions[] = { "VK_KHR_surface", "VK_KHR_win32_surface" };
#elif defined(HAVE_WAYLAND)
    const char* extensions[] = { "VK_KHR_surface", "VK_KHR_wayland_surface" };
#else
    const char* extensions[] = { "VK_KHR_surface", "VK_KHR_xlib_surface" };
#endif
    createInfo.enabledExtensionCount = 2;
    createInfo.ppEnabledExtensionNames = extensions;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance");
    }

#ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.hwnd = static_cast<HWND>(nativeWindow);
    surfaceInfo.hinstance = GetModuleHandle(nullptr);

    if (vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Win32 surface");
    }
#elif defined(HAVE_WAYLAND)
    VkWaylandSurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.display = reinterpret_cast<wl_display*>(nativeDisplay);
    surfaceInfo.surface = reinterpret_cast<wl_surface*>(nativeWindow);

    if (vkCreateWaylandSurfaceKHR(instance, &surfaceInfo, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Wayland surface");
    }
#else
    VkXlibSurfaceCreateInfoKHR surfaceInfo{};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.window = reinterpret_cast<Window>(nativeWindow);
    surfaceInfo.dpy = reinterpret_cast<Display*>(nativeDisplay);

    if (vkCreateXlibSurfaceKHR(instance, &surfaceInfo, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Xlib surface");
    }
#endif

    std::cout << "Vulkan initialized with surface." << std::endl;
}

void VulkanRenderer::selectPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("No Vulkan-compatible GPU found!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // Pick the first available device for now
    physicalDevice = devices[0];

    // Find a queue family that supports graphics
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    uint32_t graphicsFamilyIndex = -1;
    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            graphicsFamilyIndex = i;
            break;
        }
    }

    if (graphicsFamilyIndex == -1) {
        throw std::runtime_error("Failed to find a graphics queue family!");
    }

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = graphicsFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;

    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical Vulkan device!");
    }

    vkGetDeviceQueue(device, graphicsFamilyIndex, 0, &graphicsQueue);
}


void VulkanRenderer::cleanup() {
    if (fontImageView != VK_NULL_HANDLE) {
        vkDestroyImageView(device, fontImageView, nullptr);
    }
    if (fontImage != VK_NULL_HANDLE) {
        vkDestroyImage(device, fontImage, nullptr);
    }
    if (fontImageMemory != VK_NULL_HANDLE) {
        vkFreeMemory(device, fontImageMemory, nullptr);
    }
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
    }
}

void VulkanRenderer::beginFrame() {
    std::cout << "[Vulkan] Begin Frame" << std::endl;
}

void VulkanRenderer::endFrame() {
    std::cout << "[Vulkan] End Frame" << std::endl;
}

void VulkanRenderer::drawTextOverlay(const std::string& message) {
    std::cout << "[Overlay] " << message << std::endl;
}

int VulkanRenderer::getFramebufferWidth() const {
    // Stub - Replace with actual swapchain extent
    return 800;
}

int VulkanRenderer::getFramebufferHeight() const {
    // Stub - Replace with actual swapchain extent
    return 600;
}

void VulkanRenderer::drawTextOverlayLine(const std::string& text, int x, int y) {
    // Stub - Replace with Vulkan draw calls
    std::cout << "Draw text at (" << x << "," << y << "): " << text << std::endl;
}

void VulkanRenderer::loadFontTexture() {
    int width, height, channels;
    unsigned char* pixels = stbi_load("../assets/font.png", &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels) {
        throw std::runtime_error("Failed to load font texture image");
    }

    std::cout << "Loaded font texture: " << width << "x" << height << ", channels: " << channels << std::endl;

    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateImage(device, &imageInfo, nullptr, &fontImage) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create font texture image");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, fontImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = 0; // To be selected based on memory type bits

    if (vkAllocateMemory(device, &allocInfo, nullptr, &fontImageMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate memory for font texture image");
    }

    vkBindImageMemory(device, fontImage, fontImageMemory, 0);

    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = fontImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (vkCreateImageView(device, &viewInfo, nullptr, &fontImageView) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create font texture image view");
    }

    stbi_image_free(pixels);
}
