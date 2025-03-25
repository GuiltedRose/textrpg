#pragma once

#include "GameWindow.h"
#include <memory>
#include <string>

// Returns a platform-specific implementation of GameWindow.
// Throws std::runtime_error if no suitable platform is available.
std::unique_ptr<GameWindow> CreatePlatformWindow(const std::string& title, int width, int height);