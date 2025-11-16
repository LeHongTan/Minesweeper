#ifndef GAME_H
#define GAME_H

#include "../config.h"

class UIGame;

// -- BOMBS -- //
const int NUM_BOMBS = 15;
const int BOMB_VALUE = -1;

class CoreGame {
    private:
        int _gameBoard[GRID_SIZE_Y][GRID_SIZE_X];
        bool _isCellRevealed[GRID_SIZE_Y][GRID_SIZE_X];

        int _offsetX;
        int _offsetY;

        int _cntCellRevealed;
        bool _isPlaced[GRID_SIZE_Y][GRID_SIZE_X];

        bool _isGameOver;
        bool _isWin;

    public:
        CoreGame();
        ~CoreGame();

        int getOffsetX();
        int getOffsetY();
        bool checkCellRevealed(int, int);
        int getGameBoard(int, int);
        bool checkPlaced(int, int);
        bool checkGameOver();
        bool checkWin();

        void HandleInput();
        void checkStateGame();
        void RevealCell(int, int);
};

#endif