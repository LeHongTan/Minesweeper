#include "game.h"
#include "raylib.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cmath>
#include <algorithm>

CoreGame::CoreGame() {
    _offsetX = (SCREEN_WIDTH - CELL_SIZE * GRID_SIZE_X) / 2;
    _offsetY = (SCREEN_HEIGHT - CELL_SIZE * GRID_SIZE_Y) / 2;

    _gameState = STATE_MENU; 
    ResetGame(); 
}

CoreGame::~CoreGame() {
    std::cout << "LOG: Core game closed\n";
}

void CoreGame::ResetGame() {
    std::cout << "LOG: Resetting game...\n";
    _cntCellRevealed = 0;
    _isGameOver = false;
    _isWin = false;

    _startTime = GetTime();
    _fixedTime = -1;

    for (int y = 0; y < GRID_SIZE_Y; ++y) {
        for (int x = 0; x < GRID_SIZE_X; ++x) {
            _gameBoard[y][x] = 0;
            _isCellRevealed[y][x] = false;
            _isPlaced[y][x] = false;
        }
    }

    // Create Bombs
    int bombsPlaced = 0;
    while (bombsPlaced < NUM_BOMBS) {
        int y = rand() % GRID_SIZE_Y;
        int x = rand() % GRID_SIZE_X;
        if (_gameBoard[y][x] != BOMB_VALUE) {
            _gameBoard[y][x] = BOMB_VALUE;
            ++bombsPlaced;
        }
    }

    // Calculate Numbers
    for (int y = 0; y < GRID_SIZE_Y; ++y) {
        for (int x = 0; x < GRID_SIZE_X; ++x) {
            if (_gameBoard[y][x] == BOMB_VALUE) continue;
            int cntBombs = 0;
            for (int index_y = std::max(0, y - 1); index_y <= std::min(GRID_SIZE_Y - 1, y + 1); ++index_y) {
                for (int index_x = std::max(0, x - 1); index_x <= std::min(GRID_SIZE_X - 1, x + 1); ++index_x) {
                    if (index_x == x && index_y == y) continue;
                    if (_gameBoard[index_y][index_x] == BOMB_VALUE) ++cntBombs;
                }
            }
            _gameBoard[y][x] = cntBombs;
        }
    }
}

void CoreGame::StartGame() {
    ResetGame();
    _gameState = STATE_PLAYING;
}

// Getters 
int CoreGame::getOffsetX() { return _offsetX; }
int CoreGame::getOffsetY() { return _offsetY; }
bool CoreGame::checkCellRevealed(int y, int x) { return _isCellRevealed[y][x]; }
int CoreGame::getGameBoard(int y, int x) { return _gameBoard[y][x]; }
bool CoreGame::checkPlaced(int y, int x) { return _isPlaced[y][x]; }
bool CoreGame::checkGameOver() { return _isGameOver; }
bool CoreGame::checkWin() { return _isWin; }
GameState CoreGame::getGameState() { return _gameState; }
int CoreGame::getTimePlayed() {
    if (_fixedTime >= 0) {
        return (int)_fixedTime;
    }
    return (int)(GetTime() - _startTime);
}

void CoreGame::HandleInput()
{
    if (_gameState == STATE_MENU) {
        float btnX = (SCREEN_WIDTH - MENU_WIDTH) / 2;
        float btnY = (SCREEN_HEIGHT - MENU_HEIGHT) / 2.0f + 50; 

        Rectangle startBtn = { btnX, btnY, (float)MENU_WIDTH, (float)MENU_HEIGHT };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), startBtn))
                StartGame(); 
        }
        return; 
    }

    if (_isGameOver || _isWin) {
        float panelY = (SCREEN_HEIGHT - PANEL_HEIGHT) / 2.0f;
        float btnY = panelY + PANEL_HEIGHT - RESET_BTN_HEIGHT - 30;
        float btnX = (SCREEN_WIDTH - RESET_BTN_WIDTH) / 2.0f;

        Rectangle playAgainBtn = { btnX, btnY, (float)RESET_BTN_WIDTH, (float)RESET_BTN_HEIGHT };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), playAgainBtn)) {
                StartGame();
            }
        }
        return; 
    }

    Rectangle topResetBtn = { (SCREEN_WIDTH - RESET_BTN_WIDTH) / 2.0f, (float)RESET_BTN_MARGIN_TOP, (float)RESET_BTN_WIDTH, (float)RESET_BTN_HEIGHT };
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), topResetBtn)) {
            ResetGame();
            return;
        }
    }

    // Grid Click
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int local_x = mouseX - _offsetX;
    int local_y = mouseY - _offsetY;
    int cellX = local_x / CELL_SIZE;
    int cellY = local_y / CELL_SIZE;

    if (cellX >= 0 && cellX < GRID_SIZE_X && cellY >= 0 && cellY < GRID_SIZE_Y) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!_isPlaced[cellY][cellX]) RevealCell(cellY, cellX);
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            if (!_isCellRevealed[cellY][cellX]) _isPlaced[cellY][cellX] = !_isPlaced[cellY][cellX];
        }
    }
}

void CoreGame::checkStateGame() {
    _isWin = (_cntCellRevealed == GRID_SIZE_X * GRID_SIZE_Y - NUM_BOMBS);
}

void CoreGame::RevealCell(int y, int x) {
    if (y < 0 || y >= GRID_SIZE_Y || x < 0 || x >= GRID_SIZE_X) return;
    if (_isCellRevealed[y][x]) return;
    if (_isPlaced[y][x]) return;

    if (_gameBoard[y][x] == BOMB_VALUE) {
        _isGameOver = true;
        _fixedTime = GetTime() - _startTime;
        for (int r = 0; r < GRID_SIZE_Y; ++r) {
            for (int c = 0; c < GRID_SIZE_X; ++c) {
                if (_gameBoard[r][c] == BOMB_VALUE) _isCellRevealed[r][c] = true;
            }
        }
        return;
    }

    _isCellRevealed[y][x] = true;
    ++_cntCellRevealed;

    checkStateGame();
    if (_isWin) { _isGameOver = true; _fixedTime = GetTime() - _startTime; }

    if (_gameBoard[y][x] == 0) {
        for (int index_y = std::max(0, y - 1); index_y <= std::min(GRID_SIZE_Y - 1, y + 1); ++index_y) {
            for (int index_x = std::max(0, x - 1); index_x <= std::min(GRID_SIZE_X - 1, x + 1); ++index_x) {
                if (index_x == x && index_y == y) continue;
                RevealCell(index_y, index_x);
            }
        }
    }
}