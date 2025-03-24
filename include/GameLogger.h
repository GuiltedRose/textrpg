#pragma once
#include <iostream>
#include <sstream>
#include "GameWindow.h"

class GameLogger {
public:
    static void setWindow(GameWindow* gw);
    static void info(const std::string& message);
    static void clear();

private:
    static GameWindow* window;
};