#include "systems/GlyphLayout.h"
#include <algorithm>

namespace GlyphLayout {

    std::vector<GlyphInstance> generateGlyphs(
        const std::string& text,
        int startX,
        int startY,
        const FontMetrics& metrics
    ) {
        std::vector<GlyphInstance> glyphs;
        int cursorX = startX;
        int cursorY = startY;

        for (char c : text) {
            if (c == '\n') {
                cursorX = startX;
                cursorY += metrics.glyphHeight;
                continue;
            }

            int index = static_cast<unsigned char>(c);
            int col = index % metrics.textureColumns;
            int row = index / metrics.textureColumns;

            float uvX = static_cast<float>(col * metrics.glyphWidth) / (metrics.glyphWidth * metrics.textureColumns);
            float uvY = static_cast<float>(row * metrics.glyphHeight) / (metrics.glyphHeight * metrics.textureColumns);
            float uvW = static_cast<float>(metrics.glyphWidth) / (metrics.glyphWidth * metrics.textureColumns);
            float uvH = static_cast<float>(metrics.glyphHeight) / (metrics.glyphHeight * metrics.textureColumns);

            GlyphInstance glyph;
            glyph.pos = glm::vec2(cursorX, cursorY);
            glyph.uvTopLeft = glm::vec2(uvX, uvY);
            glyph.uvBottomRight = glm::vec2(uvX + uvW, uvY + uvH);
            glyphs.push_back(glyph);

            cursorX += metrics.glyphWidth;
        }

        return glyphs;
    }

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
    ) {
        std::vector<GlyphInstance> glyphs;
        std::vector<std::string> lines;
        std::string currentLine;

        float scaledWidth = glyphWidth * scale * charSpacing;
        float scaledHeight = (lineHeight > 0.0f ? lineHeight : glyphHeight) * scale;

        // Split into lines
        for (char c : text) {
            if (c == '\n') {
                lines.push_back(currentLine);
                currentLine.clear();
            } else {
                currentLine += c;
            }
        }
        if (!currentLine.empty()) {
            lines.push_back(currentLine);
        }

        for (size_t row = 0; row < lines.size(); ++row) {
            std::string line = lines[row];
            if (forceUppercase) {
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
            }

            float lineWidth = line.size() * scaledWidth;
            float xOffset = 0.0f;
            switch (alignment) {
                case Alignment::Center:
                    xOffset = -lineWidth / 2.0f;
                    break;
                case Alignment::Right:
                    xOffset = -lineWidth;
                    break;
                case Alignment::Left:
                default:
                    xOffset = 0.0f;
                    break;
            }


            for (size_t i = 0; i < line.size(); ++i) {
                unsigned char ascii = static_cast<unsigned char>(line[i]);

                float u = (ascii % static_cast<int>(textureColumns)) / textureColumns;
                float v = (ascii / static_cast<int>(textureColumns)) / textureRows;

                float uvStepX = 1.0f / textureColumns;
                float uvStepY = 1.0f / textureRows;

                GlyphInstance instance;
                instance.pos = glm::vec2(startX + xOffset + i * scaledWidth, startY + row * scaledHeight);
                instance.uvTopLeft = glm::vec2(u, v);
                instance.uvBottomRight = glm::vec2(u + uvStepX, v + uvStepY);
                glyphs.push_back(instance);
            }
        }

        return glyphs;
    }

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
    ) {
        std::vector<GlyphInstance> glyphs;
        float scaledWidth = glyphWidth * scale;
        float scaledHeight = glyphHeight * scale;

        for (size_t row = 0; row < lines.size(); ++row) {
            std::string line = lines[row];

            if (forceUppercase) {
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);
            }

            float lineWidth = static_cast<float>(line.size()) * scaledWidth;
            float xOffset = 0.0f;
            switch (alignment) {
                case Alignment::Center:
                    xOffset = -lineWidth / 2.0f;
                    break;
                case Alignment::Right:
                    xOffset = -lineWidth;
                    break;
                case Alignment::Left:
                default:
                    xOffset = 0.0f;
                    break;
            }

            for (size_t i = 0; i < line.size(); ++i) {
                unsigned char ascii = static_cast<unsigned char>(line[i]);

                float u = (ascii % static_cast<int>(textureColumns)) / textureColumns;
                float v = (ascii / static_cast<int>(textureColumns)) / textureRows;

                float uvStepX = 1.0f / textureColumns;
                float uvStepY = 1.0f / textureRows;

                GlyphInstance instance;
                instance.pos = glm::vec2(startX + xOffset + i * scaledWidth, startY + row * scaledHeight * lineSpacing);
                instance.uvTopLeft = glm::vec2(u, v);
                instance.uvBottomRight = glm::vec2(u + uvStepX, v + uvStepY);

                glyphs.push_back(instance);
            }
        }

        return glyphs;
    }
} 