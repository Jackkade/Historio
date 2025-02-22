#include <iostream>
#include <string>
using std::string;
#include "raylib.h"

#include "Pop.h"

int main(int, char**) {

    Font pixantiqua_font = LoadFont("resources/fonts/pixantiqua.png");

    const Color bgColor = {25, 25, 25, 255};

    InitWindow(1280, 720, "Historio");
    SetTargetFPS(60);

    //  Game Mechanics
    Location location_1(Tropical, Flat, Farmlands);
    
    Pop tribe(100, location_1);

    string TribePopStr = "Population: ";

    while(!WindowShouldClose()) {
        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(bgColor);

        /*//     Update Objects     //*/
        tribe.update();


        /*//     Draw User Interface (UI)     //*/
        DrawTextEx(pixantiqua_font, "Tribe", Vector2{15, 15}, 40, 5, Color{45, 100, 200, 255});
        TribePopStr = ("Population: " + std::to_string(tribe.getPopulation()));
        DrawTextEx(pixantiqua_font, TribePopStr.c_str(), Vector2{15, 60}, 40, 5, Color{45, 100, 200, 255});
        //DrawTextEx(pixantiqua_font, "Hello Historio", Vector2{10, 15}, 40, 5, Color{45, 100, 200, 255});

        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
