#pragma once

#include "GameWindow.h"
#include <X11/Xlib.h>

class PlatformLinux : public GameWindow {
    public:
        PlatformLinux(const std::string& title, int width, int height);
        ~PlatformLinux();
    
        std::string GetPlatformName() const override { return "X11"; }
    
        void clear() override;
        void refresh() override;
    
        void PollEvents() override;
        bool ShouldClose() const override;
        void* GetNativeWindowHandle() const override;
        void* GetNativeDisplayHandle() const override;
    
    private:
        Display* display = nullptr;
        Window window = 0;
        int screen = 0;
        bool shouldClose = false;
    };