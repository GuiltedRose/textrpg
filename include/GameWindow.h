#pragma once
#include <string>

class GameWindow {
    public:
        virtual ~GameWindow() = default;
    
        virtual void createWindow() = 0;         // ← Add this
        virtual void clear() = 0;                // ← Add this
        virtual void drawText(const std::string& text) = 0;
        virtual void refresh() = 0;
        virtual void setWriteMode(bool enabled) = 0;
        virtual char waitForCharInput() = 0;
        virtual std::string waitForLineInput() = 0;
    };
    
    