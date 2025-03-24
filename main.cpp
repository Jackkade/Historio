#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#include <iostream>
#include <string>
using std::string;
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Pop.h"
#include "Location.h"
#include "Settlement.h"

int main(int, char**) {

    bool WindowBox005Active = true;
    bool TextBox003EditMode = false;
    char TextBox002Text[128] = "SAMPLE TEXT";
    bool LabelButton002Pressed = false;
    bool LabelButton003Pressed = false;
    bool LabelButton004Pressed = false;

    GuiSetFont(LoadFont("resources/fonts/pixantiqua.png"));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Historio");
    SetTargetFPS(60);

    //  Game Mechanics
    Location location_1(Temperate, Flat, Farmlands);
    location_1.changeName("Judith");
    strncpy(TextBox002Text, location_1.getName().c_str(), 128);

    Settlement settlement_1(&location_1);

    Pop tribe(100, settlement_1);

    string TribePopStr = "Population: ";
    string TribeUnrestStr = "Unrest: ";


    while(!WindowShouldClose()) {
        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        
        
        
        /*//     Update Objects     //*/
        tribe.update();
        
        
        
        
        /*//     Draw User Interface (UI)     //*/
        //      Pop (Tribe) Info
        TribePopStr = ("Population: " + std::to_string(settlement_1.getPopulation()));
        TribeUnrestStr = ("Unrest: " + std::to_string(tribe.getUnrest()));        
        
        //      Location Info
        if (WindowBox005Active) {
            WindowBox005Active = !GuiWindowBox((Rectangle){ 312, 192, 464, 320 }, "");
            if (GuiTextBox((Rectangle){ 320, 232, 120, 24 }, TextBox002Text, 128, TextBox003EditMode)) {
                TextBox003EditMode = !TextBox003EditMode;
                location_1.changeName(TextBox002Text);
            }
            LabelButton002Pressed = GuiButton((Rectangle){ 320, 480, 120, 24 }, std::to_string(location_1.getClimate()).c_str());
            LabelButton003Pressed = GuiButton((Rectangle){ 320, 448, 120, 24 }, TribePopStr.c_str());
            LabelButton004Pressed = GuiButton((Rectangle){ 320, 416, 120, 24 }, TribeUnrestStr.c_str());
        }
        else {
            WindowBox005Active = GuiButton((Rectangle){ 312, 192, 120, 24 }, "SAMPLE TEXT");
        }


        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
