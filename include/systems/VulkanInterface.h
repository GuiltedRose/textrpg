#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class VulkanRenderer {
public:
    VulkanRenderer(void* nativeWindow, void* nativeDisplay);
    ~VulkanRenderer();

    void loadFontTexture();

    void beginFrame();
    void endFrame();

    void drawTextOverlay(const std::string& message);  // Placeholder stub

    int getFramebufferWidth() const;
    int getFramebufferHeight() const;

    void drawTextOverlayLine(const std::string& text, int x, int y);

private:
    void initVulkan();
    void cleanup();
    void selectPhysicalDevice();

    void* nativeWindow;
    void* nativeDisplay;
    
    VkImage fontImage = VK_NULL_HANDLE;
    VkDeviceMemory fontImageMemory = VK_NULL_HANDLE;
    VkImageView fontImageView = VK_NULL_HANDLE;
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    VkImageCreateInfo imageInfo;
    // Add more as needed
};