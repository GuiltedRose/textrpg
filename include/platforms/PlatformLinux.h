#pragma once

#include "GameWindow.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>
#include <vector>

class PlatformWindowLinux : public GameWindow {
public:
    PlatformWindowLinux();               // ← Add this
    ~PlatformWindowLinux() override;

    void createWindow() override;
    void clear() override;
    void drawText(const std::string& text) override;
    void refresh() override;
    void setWriteMode(bool enabled) override;
    char waitForCharInput() override;
    std::string waitForLineInput() override;  // ← REQUIRED now!

    void handleRawInput(char input);               // ← NEW
    void handleKeyPress(char input);               // ← NEW
    void run();      

private:
    Display* display = nullptr;
    Window window;
    GC gc;
    XFontStruct* font = nullptr;
    int cursorX = 10;
    int cursorY = 20;
    const int windowWidth = 800;
    const int windowHeight = 600;
    bool writeMode = true;

    std::vector<std::string> lines;
};
