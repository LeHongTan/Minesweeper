#ifndef UI_H
#define UI_H

#include "../config.h"
#include "raylib.h"

class CoreGame;

class UIGame {
    public:
        UIGame();
        ~UIGame();

        void ColorValue(Color&, int);
        void DrawBtn(float, float, const char*, int);
        void DrawGame(CoreGame&);
};

#endif