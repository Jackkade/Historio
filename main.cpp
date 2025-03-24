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

void drawButtons(Rectangle bounds, Vector2 scroll) {
    for (int i = 0; i < 100; i++ ) {
        GuiButton((Rectangle){ bounds.x + 4, bounds.y + scroll.y + i * 30, 120, 24 }, "woasw");
    } 
}

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
    Location location_1(Oceanic, Flat, Farmlands);
    location_1.changeName("Judith");
    strncpy(TextBox002Text, location_1.getName().c_str(), 128);

    Settlement settlement_1(&location_1);

    Pop tribe(100, settlement_1);

    string TribePopStr = "Population: ";
    string TribeUnrestStr = "Unrest: ";


    Rectangle scrollPanel = {316, 408, 128, 228};
    Rectangle panelContentRec = {0, 0, 128, 1340 };
    Rectangle rect1 = {0, 0, 0, 0};
    Vector2 scroll = {0, 0};

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
            GuiScrollPanel(scrollPanel, NULL, panelContentRec, &scroll, &rect1);
            BeginScissorMode(rect1.x, rect1.y, rect1.width, rect1.height);
                //drawButtons(scrollPanel, scroll);
                
                LabelButton004Pressed = GuiButton((Rectangle){ scrollPanel.x + 4, scrollPanel.y + scroll.y,      120, 24 }, TribeUnrestStr.c_str());
                LabelButton003Pressed = GuiButton((Rectangle){ scrollPanel.x + 4, scrollPanel.y + scroll.y + 30, 120, 24 }, TribePopStr.c_str());
                LabelButton002Pressed = GuiButton((Rectangle){ scrollPanel.x + 4, scrollPanel.y + scroll.y + 60, 120, 24 }, std::to_string(location_1.getClimate()).c_str());
                
            EndScissorMode();
        }
        else {
            WindowBox005Active = GuiButton((Rectangle){ 312, 192, 120, 24 }, "SAMPLE TEXT");
        }


        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
