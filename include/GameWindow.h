#pragma once

#include <string>

class VulkanRenderer;

class GameWindow {
public:
    virtual ~GameWindow() = default;
    
    virtual void PollEvents() = 0;
    virtual bool ShouldClose() const = 0;
    virtual void clear() = 0;
    virtual void refresh() = 0;
    
    virtual void* GetNativeWindowHandle() const = 0;
    virtual void* GetNativeDisplayHandle() const = 0;

    virtual VulkanRenderer& getRenderer() = 0;
        
    virtual std::string GetPlatformName() const = 0;
    virtual bool isKeyPressed(int keyCode) const = 0;
    virtual bool isKeyPressed(const std::string&) const = 0;
};