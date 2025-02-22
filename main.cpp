#include <iostream>
#include "raylib.h"

#include "Pop.h"

int main(int, char**) {

    Font pixantiqua_font = LoadFont("resources/fonts/pixantiqua.png");

    const Color bgColor = {25, 25, 25, 255};

    InitWindow(1280, 720, "Historio");



    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bgColor);

        

        DrawTextEx(pixantiqua_font, "Hello Historio", Vector2{10, 10}, 40, 5, Color{45, 100, 200, 255});

        EndDrawing();
    }
    CloseWindow();
}
