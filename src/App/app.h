#ifndef APP_H
#define APP_H

#include "raylib.h"
#include "../Core/game.h"
#include "../UI/ui.h"

class App {
    public:
        App(); 
        ~App();

        void RunApp(CoreGame&, UIGame&);
};

#endif