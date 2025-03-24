#pragma once

#include <string>
#include <limits>

class GameWindow;

int getIntInput(GameWindow* window, const std::string& prompt, int min, int max);
std::string getLineInput(GameWindow* window, const std::string& prompt);

char getCharInputRaw(GameWindow* window, const std::string& prompt = "");
char getCharInput(GameWindow* window, const std::string& prompt);