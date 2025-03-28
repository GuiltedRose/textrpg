#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct GlyphInstance {
    glm::vec2 pos;
    glm::vec2 uvTopLeft;
    glm::vec2 uvBottomRight;
};

class VulkanTextRenderer {
public:
VulkanTextRenderer(VkDevice device, VkPhysicalDevice physicalDevice, VkRenderPass renderPass, VkExtent2D swapchainExtent);
    ~VulkanTextRenderer();

    void uploadFont(VkDeviceMemory imageMemory, VkImageView imageView, VkSampler sampler);
    void renderText(VkCommandBuffer cmd, const std::vector<GlyphInstance>& glyphs);

    static std::vector<char> readSPIRVFile(const std::string& filename);

private:
    void createDescriptorSetLayout();
    void createPipeline(VkRenderPass renderPass, VkExtent2D swapchainExtent);
    void createBuffers();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createShaderStages(VkPipelineShaderStageCreateInfo shaderStages[2]);

    static VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

    VkDevice device;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline pipeline;

    VkShaderModule vertShaderModule = VK_NULL_HANDLE;
    VkShaderModule fragShaderModule = VK_NULL_HANDLE;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexMemory;
    VkPhysicalDevice physicalDevice;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;

};
