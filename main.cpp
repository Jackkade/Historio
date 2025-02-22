#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include <string>
using std::string;
#include "raylib.h"

#include "Pop.h"

int main(int, char**) {

    Font pixantiqua_font = LoadFont("resources/fonts/pixantiqua.png");

    const Color bgColor = {25, 25, 25, 255};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Historio");
    SetTargetFPS(60);

    //  Game Mechanics
    Location location_1(Tropical, Flat, Farmlands);
    location_1.changeName("Judith");

    Pop tribe(100, location_1);

    string TribePopStr = "Population: ";
    string TribeUnrestStr = "Unrest: ";

    while(!WindowShouldClose()) {
        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(bgColor);

        /*//     Update Objects     //*/
        tribe.update();


        /*//     Draw User Interface (UI)     //*/
        //      Pop (Tribe) Info
        DrawTextEx(pixantiqua_font, "Tribe", Vector2{15, 15}, 40, 5, Color{45, 100, 200, 255});
        TribePopStr = ("Population: " + std::to_string(tribe.getPopulation()));
        DrawTextEx(pixantiqua_font, TribePopStr.c_str(), Vector2{15, 60}, 40, 5, Color{45, 100, 200, 255});
        TribeUnrestStr = ("Unrest: " + std::to_string(tribe.getUnrest()));        
        DrawTextEx(pixantiqua_font, TribeUnrestStr.c_str(), Vector2{15, 105}, 40, 5, Color{45, 100, 200, 255});
        //      Location Info
        DrawTextEx(pixantiqua_font, location_1.getName().c_str(), Vector2{SCREEN_WIDTH - 250, 15}, 40, 5, Color{45, 100, 200, 255});

        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
