#ifndef GAME_H
#define GAME_H

#include "../config.h"

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

        double _startTime;
        double _fixedTime; 

    public:
        CoreGame();
        ~CoreGame();

        void ResetGame();
        
        // Getters
        int getOffsetX();
        int getOffsetY();
        bool checkCellRevealed(int, int);
        int getGameBoard(int, int);
        bool checkPlaced(int, int);
        bool checkGameOver();
        bool checkWin();
        int getTimePlayed();

        // Logic
        void HandleInput();
        void checkStateGame();
        void RevealCell(int, int);
};

#endif