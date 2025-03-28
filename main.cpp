#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#include <iostream>
#include <string>
using std::string;
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BACKGROUND      (Color){ 30, 30, 45, 255 }          // Dark Blue
#define FOREGROUND      (Color){ 242, 222, 162, 255 }       // Light Yellow

#include "Pop.h"
#include "Location.h"
#include "Settlement.h"

void drawButtons(Rectangle bounds, Vector2 scroll) {
    for (int i = 0; i < 100; i++ ) {
        GuiButton((Rectangle){ bounds.x + 4, bounds.y + scroll.y + i * 30, 120, 24 }, "woasw");
    } 
}

int main(int, char**) {

    /*~~    GUI Variables   ~~*/
    bool LocationViewActive = true;
    bool LocationViewNameEditMode = false;
    char LocationViewName[128] = "SAMPLE TEXT";
    bool LocationViewUnrestButton = false;
    bool LocationViewPopulationButton = false;
    bool LocationViewTerrainButton = false;

    Rectangle LocationViewScrollPanelBounds = {8, 66, 160, 257};
    Rectangle LocationViewScrollPanelContent = {0, 0, 145, 600 };
    Rectangle LocationViewScrollPanelView = {0, 0, 0, 0};
    Vector2 LocationViewScrollPanelScroll = {0, 0};
    /*~~                    ~~*/


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Historio");
    SetTargetFPS(60);
    GuiLoadStyle("ancien.rgs");
    Font font = LoadFont("resources/fonts/pixantiqua.png");
    GuiSetFont(font);

    //  Game Mechanics
    Location location_1(Oceanic, Flat, Farmlands);
    location_1.changeName("Judith");
    strncpy(LocationViewName, location_1.getName().c_str(), 128);

    
    Settlement settlement_1(&location_1);
    
    Pop tribe(100, settlement_1);


    string TribePopStr = "Population: ";
    string TribeUnrestStr = "Unrest: ";

    while(!WindowShouldClose()) {
        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(BACKGROUND);

        
        
        
        /*//     Update Objects     //*/
        location_1.update();
        
        
        
        
        /*//     Draw User Interface (UI)     //*/
        //      Pop (Tribe) Info
        TribePopStr = ("Population: " + std::to_string(settlement_1.getPopulation()));
        TribeUnrestStr = ("Unrest: " + std::to_string(tribe.getUnrest()));        
        
        //      Location Info
        if (LocationViewActive) {
            LocationViewActive = !GuiWindowBox((Rectangle){ 4, 4, 420, 320 }, "");
            if (GuiTextBox((Rectangle){ 8, 32, 160, 30 }, LocationViewName, 128, LocationViewNameEditMode)) {
                LocationViewNameEditMode = !LocationViewNameEditMode;
                location_1.changeName(LocationViewName);
            }

            GuiScrollPanel(LocationViewScrollPanelBounds, 
                           NULL, 
                           LocationViewScrollPanelContent, 
                           &LocationViewScrollPanelScroll, 
                           &LocationViewScrollPanelView);

            BeginScissorMode(LocationViewScrollPanelView.x, 
                             LocationViewScrollPanelView.y, 
                             LocationViewScrollPanelView.width, 
                             LocationViewScrollPanelView.height);
                             
                //drawButtons(scrollPanel, scroll);

                LocationViewUnrestButton = GuiButton((Rectangle){ LocationViewScrollPanelBounds.x + 4, LocationViewScrollPanelBounds.y + LocationViewScrollPanelScroll.y, 140, 30 }, TribeUnrestStr.c_str());
                LocationViewPopulationButton = GuiButton((Rectangle){ LocationViewScrollPanelBounds.x + 4, LocationViewScrollPanelBounds.y + LocationViewScrollPanelScroll.y + 34, 140, 30 }, TribePopStr.c_str());
                LocationViewTerrainButton = GuiButton((Rectangle){ LocationViewScrollPanelBounds.x + 4, LocationViewScrollPanelBounds.y + LocationViewScrollPanelScroll.y + 68, 140, 30 }, std::to_string(location_1.getClimate()).c_str());
                
            EndScissorMode();
        }
        else {
            LocationViewActive = GuiButton((Rectangle){ 4, 4, 240, 30 }, "Sample Text");
        }

        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
