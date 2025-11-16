#include "ui.h"
#include "raylib.h"

#include <iostream>
#include <string>

UIGame::UIGame() 
{
    std::cout << "LOG: Loaded UI successfully\n";
}

UIGame::~UIGame() 
{
    std::cout << "LOG: Closing UI\n";
}

void UIGame::DrawGame(CoreGame& game)
{

    // RENDER
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int y = 0; y < GRID_SIZE_Y; ++y)
    {
        for (int x = 0; x < GRID_SIZE_X; ++x)
        {
            int posX = x * CELL_SIZE + game.getOffsetX();
            int posY = y * CELL_SIZE + game.getOffsetY();

            if (game.checkCellRevealed(y, x))
            {
                DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, LIGHTGRAY);

                int value = game.getGameBoard(y, x);

                if (value == BOMB_VALUE)
                {
                    DrawCircle(posX + CELL_SIZE / 2, posY + CELL_SIZE / 2, CELL_SIZE / 4, RED);
                }
                else if (value > 0)
                {
                    std::string value_str = std::to_string(value);

                    int fontSize = CELL_SIZE / 2 + 4;
                    int textWid = MeasureText(value_str.c_str(), fontSize);

                    int textX = posX + (CELL_SIZE - textWid) / 2;
                    int textY = posY + (CELL_SIZE - fontSize) / 2;

                    DrawText(value_str.c_str(), textX, textY, fontSize, BLUE);
                }
            }
            else
            {
                DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, BLACK);
                DrawRectangle(posX + 1, posY + 1, CELL_SIZE - 2, CELL_SIZE - 2, DARKGRAY);

                if (game.checkPlaced(y, x))
                {
                    DrawCircle(posX + CELL_SIZE / 2, posY + CELL_SIZE / 2, CELL_SIZE / 4, YELLOW);
                }
            }
        }
    }

    if (game.checkWin() || game.checkGameOver())
    {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f));

        std::string stateGame_str;
        int fontSize = SCREEN_HEIGHT / 2 - 300;
        game.checkWin() == true ? stateGame_str = "YOU WIN !" : stateGame_str = "GAME OVER !";
        int textWid = MeasureText(stateGame_str.c_str(), fontSize);

        DrawText(stateGame_str.c_str(), (SCREEN_WIDTH - textWid) / 2, (SCREEN_HEIGHT - fontSize) / 2, fontSize, YELLOW);
    }

    EndDrawing();
}
