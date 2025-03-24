#pragma once

#include "GameWindow.h"

class PlatformWindowMac : public GameWindow {
public:
    PlatformWindowMac();
    ~PlatformWindowMac() override;

    void createWindow() override;
    void clear() override;
    void drawText(const std::string& text) override;
    void refresh() override;
    void setWriteMode(bool enabled) override;
    char waitForCharInput() override;
    std::string waitForLineInput() override;

    void run();
};