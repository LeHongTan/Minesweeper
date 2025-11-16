# Hello guys

This is my basic ***Minesweeper*** program, created with the goal of learning and improving my programming skills.

Currently, the program is still in a rough state and lacks a dynamic or engaging user interface for players. However, I will try to improve it soon. <br>
Furthermore, the program currently features traditional gameplay, but in the near future, I will work on developing it with more interesting game modes.

This program is written *100%* in C++.

Compile game: 
```bash
clang++ -arch x86_64 -std=c++17 src/main.cpp src/App/app.cpp src/Core/game.cpp src/UI/ui.cpp -o output/game $(pkg-config --cflags --libs raylib)
``` 
Run game: 
```bash
./output/game
```