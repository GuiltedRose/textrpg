#pragma once

#include "GameWindow.h"

class PlatformWindowWindows : public GameWindow {
    public:
        PlatformWindowWindows();
        ~PlatformWindowWindows() override;
    
        void createWindow() override;
        void clear() override;
        void drawText(const std::string& text) override;
        void refresh() override;
        void setWriteMode(bool enabled) override;
        char waitForCharInput() override;
        std::string waitForLineInput() override;
    
        void handleRawInput(char input);   // optional, if used
        void handleKeyPress(char input);   // optional, if used
        void run();
    };