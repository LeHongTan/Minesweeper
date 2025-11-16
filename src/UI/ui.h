#ifndef UI_H
#define UI_H

#include "../config.h"
#include "../Core/game.h"

class UIGame {
    private:

    public:
        UIGame();
        ~UIGame();

        void DrawGame(CoreGame&);
};

#endif