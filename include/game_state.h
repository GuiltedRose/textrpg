#pragma once

enum class GameState {
    MainMenu,
    Exploring,
    Combat,
    Talking,
    GameOver,
    Exit
};

inline const char* gameStateToString(GameState state) {
    switch(state) {
        case GameState::MainMenu: return "Main Menu";
        case GameState::Exploring: return "Exploring";
        case GameState::Combat: return "In Combat";
        case GameState::Talking: return "Talking";
        case GameState::GameOver: return "Game Over";
        case GameState::Exit: return "Exit";
        default: return "Unknown";
    }
} 