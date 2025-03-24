// PlatformLinux.cpp
#include "platforms/PlatformLinux.h"
#include <iostream>
#include <cstdlib>

PlatformWindowLinux::PlatformWindowLinux() = default;

PlatformWindowLinux::~PlatformWindowLinux() {
    if (font) XFreeFont(display, font);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void PlatformWindowLinux::createWindow() {
    display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Unable to open X display!" << std::endl;
        exit(1);
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
        100, 100, windowWidth, windowHeight, 1,
        BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, KeyPressMask | ExposureMask);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, nullptr);
    font = XLoadQueryFont(display, "fixed");
    if (font) XSetFont(display, gc, font->fid);
}

void PlatformWindowLinux::drawText(const std::string& text) {
    std::cout << "[drawText] input: " << text << "\n";

    if (lines.size() > 1000) {
        std::cerr << "[drawText] Warning: lines buffer too large, trimming.\n";
        lines.erase(lines.begin());
    }

    try {
        lines.push_back(text);
    } catch (const std::exception& e) {
        std::cerr << "[drawText] Exception during push_back: " << e.what() << "\n";
    }
}

void PlatformWindowLinux::clear() {
    lines.clear();
    cursorY = 20;
    XClearWindow(display, window);
}

void PlatformWindowLinux::refresh() {
    std::cout << "[refresh] line count: " << lines.size() << std::endl;
    XClearWindow(display, window);
    int y = 20;
    for (const auto& line : lines) {
        XDrawString(display, window, gc, 10, y, line.c_str(), line.length());
        y += 20;
    }
    XFlush(display);
}

void PlatformWindowLinux::setWriteMode(bool isWriteMode) {
    writeMode = isWriteMode;
}

void PlatformWindowLinux::handleRawInput(char input) {
    if (!writeMode) {
        std::string s(1, input);
        XDrawString(display, window, gc, cursorX, cursorY, s.c_str(), 1);
        cursorX += 10;
        if (cursorX > windowWidth) {
            cursorX = 10;
            cursorY += 20;
        }
    }
}

void PlatformWindowLinux::handleKeyPress(char input) {
    if (writeMode) {
        std::string s(1, input);
        drawText(s);
        refresh();
    } else {
        handleRawInput(input);
    }
}

char PlatformWindowLinux::waitForCharInput() {
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            KeySym key = XLookupKeysym(&event.xkey, 0);
            if (key >= 32 && key <= 126) {
                return static_cast<char>(key);
            }
        }
    }
}

std::string PlatformWindowLinux::waitForLineInput() {
    std::string input;
    char ch;
    while (true) {
        ch = waitForCharInput();

        if (ch == '\n' || ch == '\r') break;
        else if (ch == '\b' || ch == 127) {
            if (!input.empty()) input.pop_back();
        } else {
            input += ch;
        }

        drawText("Input: " + input);  // Update the line
        refresh();
    }
    return input;
}

void PlatformWindowLinux::run() {
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            refresh();
        } else if (event.type == KeyPress) {
            char input = XLookupKeysym(&event.xkey, 0);
            handleKeyPress(input);
        }
    }
}
