#include "app.h"

#include <iostream>

App::App() 
{
    std::cout << "LOG: Creating APP successfully\n";
}

App::~App() 
{
    std::cout << "App closed\n";
}

void App::RunApp(CoreGame& game, UIGame& ui) {
        // Create window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper v0.1 Beta");
    SetTargetFPS(60); // game FPS

    // Loop game
    while(!WindowShouldClose()) {
        game.HandleInput();
        ui.DrawGame(game);
    }

    CloseWindow();
}