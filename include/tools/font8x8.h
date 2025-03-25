#pragma once

#include <cstdint>

extern const uint8_t font8x8_basic[128][8];

const uint8_t* getGlyph(char c);