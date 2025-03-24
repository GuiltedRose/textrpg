// input_utils.cpp
#include "input_utils.h"
#include "GameLogger.h"

std::string getLineInput(GameWindow* window, const std::string& prompt) {
    if (window) {
        GameLogger::info(prompt);
        window->setWriteMode(false);
        std::string input = window->waitForLineInput();
        window->setWriteMode(true);
        return input;
    } else {
        GameLogger::info(prompt);
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
}

int getIntInput(GameWindow* window, const std::string& prompt, int min, int max) {
    while (true) {
        std::string input = getLineInput(window, prompt);
        try {
            int value = std::stoi(input);
            if (value >= min && value <= max) {
                return value;
            }
        } catch (...) {}
        GameLogger::info("Invalid input. Please enter a number between " + std::to_string(min) + " and " + std::to_string(max) + ".");
    }
}


char getCharInputRaw(GameWindow* window, const std::string& prompt) {
    if (window) {
        GameLogger::info(prompt);
        window->setWriteMode(false);
        char ch = window->waitForCharInput();
        window->setWriteMode(true);
        return ch;
    } else {
        std::cout << prompt;
        char ch;
        std::cin >> ch;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return ch;
    }
}

char getCharInput(GameWindow* window, const std::string& prompt) {
    return getCharInputRaw(window, prompt);
}
