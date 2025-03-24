#include "platforms/PlatformWindows.h"
#include <iostream>
#include <windows.h>

PlatformWindowWindows::PlatformWindowWindows() = default;

PlatformWindowWindows::~PlatformWindowWindows() = default;

void PlatformWindowWindows::createWindow() {
    system("cls");
}

void PlatformWindowWindows::clear() {
    system("cls");
}

void PlatformWindowWindows::drawText(const std::string& text) {
    if (writeMode) {
        std::cout << text << std::endl;
    }
}

void PlatformWindowWindows::refresh() {
    // Windows console auto-refreshes; placeholder
}

void PlatformWindowWindows::setWriteMode(bool enabled) {
    writeMode = enabled;
}

char PlatformWindowWindows::waitForCharInput() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD record;
    DWORD events = 0;

    while (true) {
        ReadConsoleInput(hStdin, &record, 1, &events);
        if (record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown) {
            return record.Event.KeyEvent.uChar.AsciiChar;
        }
    }
}

std::string PlatformWindowWindows::waitForLineInput() {
    std::string input;
    while (true) {
        char ch = waitForCharInput();

        if (ch == '\r') break;  // Enter
        else if (ch == '\b' || ch == 127) {
            if (!input.empty()) input.pop_back();
        } else if (isprint(ch)) {
            input += ch;
        }

        clear();
        drawText("Input: " + input);
        refresh();
    }
    return input;
}

void PlatformWindowWindows::handleRawInput(char input) {
    drawText(std::string("[RAW INPUT] ") + input);
    refresh();
}

void PlatformWindowWindows::handleKeyPress(char input) {
    drawText(std::string("[KEY] ") + input);
    refresh();
}

void PlatformWindowWindows::run() {
    drawText("Running Windows platform window...");
    refresh();
}
