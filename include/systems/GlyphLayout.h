#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "systems/VulkanTextRenderer.h" // For GlyphInstance

namespace GlyphLayout {

enum class Alignment {
    Left,
    Center,
    Right
};

struct TextBlockConfig {
    float startX = 0;
    float startY = 0;
    float glyphWidth = 8;
    float glyphHeight = 8;
    float textureColumns = 16;
    float textureRows = 6;
    float scale = 1.0f;
    float lineSpacing = 1.0f;
    float charSpacing = 1.0f;
    GlyphLayout::Alignment alignment = GlyphLayout::Alignment::Left;
    bool forceUppercase = false;
};


struct FontMetrics {
    int glyphWidth;
    int glyphHeight;
    int textureColumns;
};

// API functions
std::vector<GlyphInstance> generateGlyphs(
    const std::string& text,
    int startX,
    int startY,
    const FontMetrics& metrics
);

std::vector<GlyphInstance> layoutGlyphs(
    const std::string& text,
    float startX,
    float startY,
    float glyphWidth,
    float glyphHeight,
    float textureColumns,
    float textureRows,
    Alignment alignment = Alignment::Left,
    float scale = 1.0f,
    float lineHeight = 0.0f,
    float charSpacing = 1.0f,
    bool forceUppercase = false
);

std::vector<GlyphInstance> drawTextLines(
    const std::vector<std::string>& lines,
    float startX,
    float startY,
    float glyphWidth,
    float glyphHeight,
    float textureColumns,
    float textureRows,
    Alignment alignment = Alignment::Left,
    float scale = 1.0f,
    float lineSpacing = 1.0f,
    bool forceUppercase = false
);

} // namespace GlyphLayout
