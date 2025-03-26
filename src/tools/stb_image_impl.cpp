// stb_image_impl.h
// Just the raw stb_image.h from Sean Barrett, modified for inclusion.
#ifndef STB_IMAGE_IMPLEMENTATION_GUARD
#define STB_IMAGE_IMPLEMENTATION_GUARD

// You may configure stb_image features here if needed (optional):
// #define STBI_NO_STDIO
// #define STBI_ONLY_PNG

#define STB_IMAGE_IMPLEMENTATION
#include <cstddef>
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

// Directly include the stb_image source (as a C header).
// This must be placed in your project directory under the same name.
#include "tools/stb_image_raw.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif // STB_IMAGE_IMPLEMENTATION_GUARD
