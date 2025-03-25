#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

class TextRenderer {
public:
    TextRenderer(VkDevice device,
                 VkPhysicalDevice physicalDevice,
                 VkQueue graphicsQueue,
                 VkCommandPool commandPool,
                 VkRenderPass renderPass);

    ~TextRenderer();

    TextRenderer(VkDevice, VkPhysicalDevice, VkRenderPass);
    void drawText(VkCommandBuffer, const std::string&, float, float, float);

private:
    void createFontTexture();
    void createDescriptorSetLayout();
    void createPipeline(VkRenderPass renderPass);
    void createVertexBuffer();

    VkDevice device;
    VkPhysicalDevice physicalDevice;
    VkQueue graphicsQueue;
    VkCommandPool commandPool;

    VkImage fontImage = VK_NULL_HANDLE;
    VkDeviceMemory fontImageMemory = VK_NULL_HANDLE;
    VkImageView fontImageView = VK_NULL_HANDLE;
    VkSampler fontSampler = VK_NULL_HANDLE;

    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline pipeline = VK_NULL_HANDLE;

    VkDescriptorSetLayout descriptorSetLayout = VK_NULL_HANDLE;
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

    VkBuffer vertexBuffer = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;
};