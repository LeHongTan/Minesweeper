#include "game.h"
#include "raylib.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib> // random
#include <string>  // draw number
#include <cmath>

CoreGame::CoreGame()
{
    // setup start value of grid
    _offsetX = (SCREEN_WIDTH - CELL_SIZE * GRID_SIZE_X) / 2;
    _offsetY = (SCREEN_HEIGHT - CELL_SIZE * GRID_SIZE_Y) / 2;

    // initializing value of placed flag
    _cntCellRevealed = 0;

    // setup state
    _isGameOver = false;
    _isWin = false;

    // setup value and state of cell
    for (int y = 0; y < GRID_SIZE_Y; ++y)
    {
        for (int x = 0; x < GRID_SIZE_X; ++x)
        {
            _gameBoard[y][x] = 0;
            _isCellRevealed[y][x] = false;
            _isPlaced[y][x] = false;
        }
    }

    // setup random general bombs
    int bombsPlaced = 0; // count bombs placed
    while (bombsPlaced < NUM_BOMBS)
    {
        int y = rand() % GRID_SIZE_Y;
        int x = rand() % GRID_SIZE_X;

        if (_gameBoard[y][x] != BOMB_VALUE)
        {
            _gameBoard[y][x] = BOMB_VALUE;
            ++bombsPlaced;
        }
    }

    // calculating neighbor counts
    for (int y = 0; y < GRID_SIZE_Y; ++y)
    {
        for (int x = 0; x < GRID_SIZE_X; ++x)
        {
            // BOMB CELL
            if (_gameBoard[y][x] == BOMB_VALUE)
                continue;

            int cntBombs = 0;
            for (int index_y = std::max(0, y - 1); index_y <= std::min(GRID_SIZE_Y - 1, y + 1); ++index_y)
            {
                for (int index_x = std::max(0, x - 1); index_x <= std::min(GRID_SIZE_X - 1, x + 1); ++index_x)
                {
                    if (index_x == x && index_y == y)
                        continue;

                    if (_gameBoard[index_y][index_x] == BOMB_VALUE)
                        ++cntBombs;
                }
            }
            _gameBoard[y][x] = cntBombs;
        }
    }

    std::cout << "LOG: Setup core game successfully!\n"; // log
}

CoreGame::~CoreGame() {
    std::cout << "LOG: Core game closed\n";
}

int CoreGame::getOffsetX() 
{
    return _offsetX;
}

int CoreGame::getOffsetY() 
{
    return _offsetY;
}

bool CoreGame::checkCellRevealed(int y, int x) 
{
    return _isCellRevealed[y][x];
}

int CoreGame::getGameBoard(int y, int x) 
{
    return _gameBoard[y][x];
}

bool CoreGame::checkPlaced(int y, int x) 
{
    return _isPlaced[y][x];
}

bool CoreGame::checkGameOver() 
{
    return _isGameOver;
}

bool CoreGame::checkWin() 
{
    return _isWin;
}

void CoreGame::HandleInput()
{
    if (_isGameOver)
        return;

    // get position of mouse
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    // change position of mouse => position of grid
    int local_x = mouseX - _offsetX;
    int local_y = mouseY - _offsetY;

    int cellX = local_x / CELL_SIZE;
    int cellY = local_y / CELL_SIZE;

    if (cellX >= 0 && cellX < GRID_SIZE_X &&
        cellY >= 0 && cellY < GRID_SIZE_Y)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!_isPlaced[cellY][cellX])
            {
                std::printf("LOG: (%d, %d) is revealed\n.", cellY, cellX);
                RevealCell(cellY, cellX);
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (!_isCellRevealed[cellY][cellX])
            {
                if (!_isPlaced[cellY][cellX])
                {
                    _isPlaced[cellY][cellX] = true;
                }
                else
                {
                    _isPlaced[cellY][cellX] = false;
                }
            }
        }
    }
}

void CoreGame::checkStateGame()
{
    _cntCellRevealed == GRID_SIZE_X *GRID_SIZE_Y - NUM_BOMBS ? _isWin = true : _isWin = false;
}

void CoreGame::RevealCell(int y, int x)
{
    // stop recursive when outside of grid
    if (y < 0 || y >= GRID_SIZE_Y ||
        x < 0 || x >= GRID_SIZE_X)
        return;

    // stop when the cell is revealed => game over
    if (_isCellRevealed[y][x])
        return;

    // stop when the cell is placed
    if (_isPlaced[y][x])
        return;

    // stop when the cell is bomb
    if (_gameBoard[y][x] == BOMB_VALUE)
    {
        _isGameOver = true;
        std::cout << "LOG: GAME OVER!\n";

        // show bomb cells
        for (int y_bomb = 0; y_bomb < GRID_SIZE_Y; ++y_bomb)
        {
            for (int x_bomb = 0; x_bomb < GRID_SIZE_X; ++x_bomb)
            {
                if (_gameBoard[y_bomb][x_bomb] == BOMB_VALUE)
                {
                    _isCellRevealed[y_bomb][x_bomb] = true;
                }
            }
        }

        return;
    }

    _isCellRevealed[y][x] = true;
    ++_cntCellRevealed;

    checkStateGame();
    if (_isWin)
    {
        std::cout << "LOG: YOU WIN!\n";
        _isGameOver = true;
    }

    // flood fill
    if (_gameBoard[y][x] == 0)
    {
        // reveal the value of neighbor cells
        for (int index_y = std::max(0, y - 1); index_y <= std::min(GRID_SIZE_Y - 1, y + 1); ++index_y)
        {
            for (int index_x = std::max(0, x - 1); index_x <= std::min(GRID_SIZE_X - 1, x + 1); ++index_x)
            {
                if (index_x == x && index_y == y)
                    continue;
                RevealCell(index_y, index_x);
            }
        }
    }
}