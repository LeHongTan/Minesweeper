#include "ui.h"
#include "../Core/game.h"
#include <iostream>
#include <string>

UIGame::UIGame() { std::cout << "LOG: Loaded UI successfully\n"; }
UIGame::~UIGame() { std::cout << "LOG: Closing UI\n"; }

void UIGame::ColorValue(Color& numberColor, int value) {
    switch (value) {
        case 1: numberColor = GetColor(0x0099FFFF); break;
        case 2: numberColor = GetColor(0xFFFF99FF); break;
        case 3: numberColor = GetColor(0xFFCC66FF); break;
        case 4: numberColor = GetColor(0xFF9900FF); break;
        case 5: numberColor = GetColor(0xFF6600FF); break;
        case 6: numberColor = GetColor(0xFF3333FF); break;
        case 7: numberColor = GetColor(0x990033FF); break;
        case 8: numberColor = GetColor(0x660000FF); break;
        default: numberColor = BLACK; break;
    }
}

void UIGame::DrawBtn(float x, float y, const char* text, int fontSize) {
    Rectangle btnRect = { x, y, (float)RESET_BTN_WIDTH, (float)RESET_BTN_HEIGHT };
    bool isHover = CheckCollisionPointRec(GetMousePosition(), btnRect);

    Color btnColor = isHover ? LIGHTGRAY : GRAY; 
    Color textColor = isHover ? BLACK : WHITE;

    DrawRectangleRec(btnRect, btnColor);
    DrawRectangleLinesEx(btnRect, 2, DARKGRAY);

    int textW = MeasureText(text, fontSize);
    DrawText(text, x + (RESET_BTN_WIDTH - textW) / 2, y + (RESET_BTN_HEIGHT - fontSize) / 2, fontSize, textColor);
}

void UIGame::DrawGame(CoreGame& game)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawBtn((SCREEN_WIDTH - RESET_BTN_WIDTH) / 2, (float)RESET_BTN_MARGIN_TOP, "RESET", 20);

    int timePlayed = game.getTimePlayed();
    std::string timeText = "TIME: " + std::to_string(timePlayed);

    int textW = MeasureText(timeText.c_str(), TIMER_FONT_SIZE);
    DrawText(timeText.c_str(), TIMER_MARGIN_LEFT, TIMER_MARGIN_TOP, TIMER_FONT_SIZE, BLACK);

    for (int y = 0; y < GRID_SIZE_Y; ++y) {
        for (int x = 0; x < GRID_SIZE_X; ++x) {
            int posX = x * CELL_SIZE + game.getOffsetX();
            int posY = y * CELL_SIZE + game.getOffsetY();

            if (game.checkCellRevealed(y, x)) {
                DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
                int value = game.getGameBoard(y, x);

                if (value == BOMB_VALUE) {
                    DrawCircle(posX + CELL_SIZE / 2, posY + CELL_SIZE / 2, CELL_SIZE / 4, RED);
                } else if (value > 0) {
                    std::string value_str = std::to_string(value);
                    Color numberColor = BLACK;
                    ColorValue(numberColor, value);
                    int fontSize = CELL_SIZE / 2 + 4;
                    int textWid = MeasureText(value_str.c_str(), fontSize);
                    DrawText(value_str.c_str(), posX + (CELL_SIZE - textWid) / 2, posY + (CELL_SIZE - fontSize) / 2, fontSize, numberColor);
                }
            } else {
                DrawRectangle(posX, posY, CELL_SIZE, CELL_SIZE, BLACK); 
                DrawRectangle(posX + 1, posY + 1, CELL_SIZE - 2, CELL_SIZE - 2, DARKGRAY);
                if (game.checkPlaced(y, x)) {
                    DrawCircle(posX + CELL_SIZE / 2, posY + CELL_SIZE / 2, CELL_SIZE / 4, YELLOW);
                }
            }
        }
    }

    if (game.checkWin() || game.checkGameOver()) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

        float panelX = (SCREEN_WIDTH - PANEL_WIDTH) / 2.0f;
        float panelY = (SCREEN_HEIGHT - PANEL_HEIGHT) / 2.0f;

        DrawRectangle(panelX, panelY, PANEL_WIDTH, PANEL_HEIGHT, RAYWHITE);
        DrawRectangleLines(panelX, panelY, PANEL_WIDTH, PANEL_HEIGHT, DARKGRAY); 

        const char* title = game.checkWin() ? "YOU WIN!" : "GAME OVER!";
        Color titleColor = game.checkWin() ? GREEN : RED;
        int titleFontSize = 40;
        int titleW = MeasureText(title, titleFontSize);

        DrawText(title, panelX + (PANEL_WIDTH - titleW) / 2, panelY + 50, titleFontSize, titleColor);

        float btnY = panelY + PANEL_HEIGHT - RESET_BTN_HEIGHT - 30;
        float btnX = (SCREEN_WIDTH - RESET_BTN_WIDTH) / 2.0f;
        
        DrawBtn(btnX, btnY, "PLAY AGAIN", 20);
    }

    EndDrawing();
}