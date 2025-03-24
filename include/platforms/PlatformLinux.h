#pragma once

#include "GameWindow.h"
#include <string>
#include <X11/Xlib.h>

class PlatformWindowLinux : public GameWindow {
public:
    PlatformWindowLinux();
    ~PlatformWindowLinux() override;

    void createWindow() override;
    void clear() override;
    void drawText(const std::string& text) override;
    void refresh() override;
    void setWriteMode(bool enabled) override;
    char waitForCharInput() override;
    std::string waitForLineInput() override;

    void handleRawInput(char input);
    void handleKeyPress(char input);
    void run();

private:
    bool useWayland = false;
    bool writeMode = true;
    Display* display = nullptr; // X11 only
};