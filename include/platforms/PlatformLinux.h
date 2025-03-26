#pragma once

#include "GameWindow.h"
#include "systems/VulkanInterface.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h> 
#include <unordered_map>
#include <unordered_set>
#include <string>

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

        VulkanRenderer& getRenderer() override { return renderer; }


        bool isKeyPressed(int keyCode) const override;
        bool isKeyPressed(const std::string& keyMap) const override;
    
    private:
        VulkanRenderer renderer;
        Display* display = nullptr;
        Window window = 0;
        int screen = 0;
        bool shouldClose = false;
        std::unordered_map<std::string, int> keyMap;

    };