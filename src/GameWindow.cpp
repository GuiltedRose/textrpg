#include "GameWindow.h"
#include "GameLogger.h"
#include <iostream>

std::string GameWindow::waitForLineInput() {
    std::string input;
    while (true) {
        char ch = waitForCharInput();  // this should already exist

        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == '\b' || ch == 127) { // backspace
            if (!input.empty()) {
                input.pop_back();
            }
        } else {
            input += ch;
        }

        drawText("Enter command: " + input); // or however your rendering system works
        refresh();
    }
    return input;
}
