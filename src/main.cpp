#include "App/app.h"

int main(void) {
    App app;
    CoreGame game;
    UIGame ui;
    app.RunApp(game, ui);

    return 0;
}