#include "startscreen.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <raylib.h>
#include <string>
#include <sstream>
#include <time.h>

StartScreen::StartScreen(uint16_t x, uint16_t y, size_t *s) {
    TextBox = {
        x / 2.f,
        y / 2.f,
        100,
        20
    };
    Seed = s;
    InitWindow(x,y,"Type Seed!!!");
}

void StartScreen::Run() {
    std::string buff;
    const int MaxChars = 11;

    while(!WindowShouldClose()) {
        char key = GetCharPressed();
        if(IsKeyPressed(KEY_BACKSPACE) && !buff.empty()) buff.pop_back();
        else if(key > 0 && buff.size() < MaxChars + 1) buff += key;
        
        if(IsKeyPressed(KEY_ENTER)) {
            if(buff.empty()){
                srand(time(0));
                *Seed = rand() % RAND_MAX;
            } else {
                std::stringstream ss(buff);
                ss >> *Seed;
            }
            CloseWindow();
            return;
        }
        
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("Max Chars = 11\nLeave Empty To Random Seed\nTo Confirm press enter\nTo Exit Pesss Escape", 10, 10, 20, RED);
            DrawText(TextFormat("Seed (Numbers): %s", buff.c_str()), 20, TextBox.y, 20, BLACK); 
        EndDrawing();
    }
    
    srand(time(0));
    *Seed = rand() % RAND_MAX;
    CloseWindow();
}
