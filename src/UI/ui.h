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
        
        void DrawBtn(float x, float y, float w, float h, const char* text, int fontSize);
        
        void DrawMenu(); 
        void DrawPlayInterface(CoreGame& game); 
        
        void DrawGame(CoreGame& game);
};

#endif