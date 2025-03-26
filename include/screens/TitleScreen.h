// Screens/TitleScreen.h
#pragma once
#include <string>
#include <vector>
#include "Game.h"
#include "GameWindow.h"
#include "game_state.h"
#include "systems/VulkanInterface.h"

namespace TitleScreen {
    static const std::vector<std::string> asciiArt = {
        " __  __     __  __     __     ______   ______    ",
        "/\\ \\_\\ \\   /\\ \\/\\ \\   /\\ \\   /\\__  _\\ /\\   __  \\   ",
        "\\ \\____ \\  \\ \\ \\_\\ \\  \\ \\ \\  \\/_/\\ \\/ \\ \\  \\/\\  \\  ",
        " \\/\\_____\\  \\ \\_____\\  \\ \\_\\    \\ \\_\\  \\ \\_____\\ ",
        "  \\/_____/   \\/_____/   \\/_/     \\/_/   \\/_____/ ",
        "",
        "        : Threads of the Unbound                "
    };

    void draw(VulkanRenderer& renderer);
    GameState updateAndDraw(GameWindow&, Game&, VulkanRenderer&);

}
