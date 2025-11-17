#include "App/app.h"
#include "config.h" 
#include <ctime>
#include <cstdlib>

int main(void) {
    srand(time(NULL));

    App app;
    CoreGame game;
    UIGame ui;
    
    app.RunApp(game, ui);

    return 0;
}