#include "tools/TextRenderer.h"
#include "tools/font8x8.h"
#include <stdexcept>
#include <cstring>

TextRenderer::TextRenderer(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkCommandPool commandPool, VkRenderPass renderPass);

    : device(device), physicalDevice(physicalDevice) {
    createFontTexture();
    createDescriptorSetLayout();
    createPipeline(renderPass);
    createVertexBuffer();
}

TextRenderer::~TextRenderer() {
    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
    vkDestroyPipeline(device, pipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
    vkDestroyImageView(device, fontImageView, nullptr);
    vkDestroyImage(device, fontImage, nullptr);
    vkFreeMemory(device, fontImageMemory, nullptr);
    vkDestroySampler(device, fontSampler, nullptr);
}

void TextRenderer::createFontTexture() {
    // TODO: Copy font8x8_basic into a 1024x8 single-channel image
    // Create a Vulkan texture and upload the data
    // Set fontImage, fontImageMemory, fontImageView, fontSampler
}

void TextRenderer::createDescriptorSetLayout() {
    // TODO: Create descriptor set layout for sampled image (font)
}

void TextRenderer::createPipeline(VkRenderPass renderPass) {
    // TODO: Create shaders, pipeline layout, and graphics pipeline
    // Load SPIR-V shaders, define vertex format, etc.
}

void TextRenderer::createVertexBuffer() {
    // TODO: Create vertex buffer and allocate memory
    // Will be updated each frame based on glyph positions
}

void TextRenderer::drawText(VkCommandBuffer cmdBuffer, const std::string& text, float x, float y, float scale) {
    // TODO: Fill vertex buffer with quads for each glyph
    // Bind pipeline, descriptor sets, vertex buffer
    // Issue draw calls for all characters in the string
}