#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

// -- WINDOW -- //
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

// -- GRID -- //
const int GRID_SIZE_X = 10;
const int GRID_SIZE_Y = 10;
const int CELL_SIZE = 40;

// -- GAMEPLAY -- //
const int BOMB_VALUE = -1;
const int NUM_BOMBS = 10;

// -- UI: TOP BAR -- //
const int RESET_BTN_WIDTH = 120;
const int RESET_BTN_HEIGHT = 40;
const int RESET_BTN_MARGIN_TOP = 20;

// Thêm vị trí cho Timer (Cách lề phải 50px)
const int TIMER_MARGIN_LEFT = 50;
const int TIMER_MARGIN_TOP = 25;
const int TIMER_FONT_SIZE = 30;

// -- UI: GAME OVER PANEL -- //
const int PANEL_WIDTH = 400;
const int PANEL_HEIGHT = 250;

#endif