#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#include <iostream>
#include <map>
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

//~~    Strings to use for GUI
std::map<Climate, string> climateNames = {
    {Oceanic, "Oceanic"},
    {Temperate, "Temperate"},
    {Subtropical, "Subtropical"},
    {Tropical, "Tropical"},
    {Arid, "Arid"},
    {Mediterranian, "Mediterranian"},
    {Arctic, "Arctic"}
};
std::map<Terrain, string> terrainNames = {
    {Wetlands, "Wetlands"},
    {Floodplains, "Floodplains"},
    {Flat, "Flat"},
    {RollingHills, "Rolling Hills"},
    {RuggedHills, "Rugged Hills"},
    {Plateau, "Plateau"},
    {Mountains, "Mountains"}
};
std::map<Vegetation, string> vegetationNames = {
    {Farmlands, "Farmlands"},
    {Grasslands, "Grasslands"},
    {Woods, "Woods"},
    {Forest, "Forest"},
    {DenseForest, "Dense Forest"},
    {Sparce, "Sparce"},
    {Barren, "Barren"}
};
std::map<Rank, string> rankNames = {
    {Camp, "Camp"},
    {Community, "Community"},
    {Village, "Village"},
    {City, "City"},
    {Metropolis, "Metropolis"},
    {Megalopolis, "Megalopolis"}
};
//~~    Eventually these should be brought into their own file, but need to be here to build for now

void drawButtons(Rectangle bounds, Vector2 scroll, Location *l, Settlement* &select) {
    bool selected = false;
    selected = GuiButton((Rectangle){ bounds.x + 4, bounds.y + scroll.y + 26, 140, 18 }, l->getCountryside()->getName().c_str());
    if(selected) {
        select = l->getCountryside();
        selected = false;
    }
    for (int i = 1; i < l->getSettlementAmount(); ++i ) {
        selected = GuiButton((Rectangle){ bounds.x + 4, bounds.y + scroll.y + i * 20 + 26, 140, 18 }, l->getSettlement(i)->getName().c_str());
        if(selected) {
            select = l->getSettlement(i);
        }
        selected = false;
    }

}

int main(int, char**) {

    /*~~    GUI Variables   ~~*/
    bool LocationViewActive = true;
    bool LocationViewNameEditMode = false;
    char LocationViewName[128] = "SAMPLE TEXT";

    Rectangle LocationViewScrollPanelBounds = {8, 66, 160, 154};
    Rectangle LocationViewScrollPanelContent = {0, 0, 145, 600 };
    Rectangle LocationViewScrollPanelView = {0, 0, 0, 0};
    Vector2 LocationViewScrollPanelScroll = {0, 0};

    string LocationViewDisplayStrings[12];
    /*~~                    ~~*/


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Historio");
    SetTargetFPS(60);
    GuiLoadStyle("ancien.rgs");
    Font font = LoadFont("resources/fonts/pixantiqua.png");
    GuiSetFont(font);

    //  Game Mechanics
    Location location_1(Oceanic, Flat, Farmlands);
    location_1.changeName("Eden");
    strncpy(LocationViewName, location_1.getName().c_str(), 128);
    
    Settlement settlement_1(&location_1);
    settlement_1.changeName("Adam");

    Settlement settlement_2(&location_1);
    settlement_2.changeName("Eve");

    Settlement settlement_3(&location_1);
    settlement_3.changeName("Seth");

    Pop tribe(100, settlement_1);

    Settlement* selectedSettlement = &settlement_1;

    while(!WindowShouldClose()) {
        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(BACKGROUND);

        
        
        
        /*//     Update Objects     //*/
        location_1.update();
        
        
        
        
        /*//     Draw User Interface (UI)     //*/
        //      Pop Info
        LocationViewDisplayStrings[0] = ("Population: " + std::to_string(location_1.getPopulation()));
        LocationViewDisplayStrings[1] = ("Unrest: " + std::to_string(tribe.getUnrest()));        
        LocationViewDisplayStrings[2] = ("Food: " + std::to_string(tribe.getFood()));        
        LocationViewDisplayStrings[3] = ("SOL: " + std::to_string(tribe.getSOL()));
        
        //      Location Info
        LocationViewDisplayStrings[4] = ("Climate: " + climateNames.at(location_1.getClimate()));
        LocationViewDisplayStrings[5] = ("Terrain: " + terrainNames.at(location_1.getTerrain()));
        LocationViewDisplayStrings[6] = ("Vegetation: " + vegetationNames.at(location_1.getVegetation()));

        LocationViewDisplayStrings[7] = ("Development: " + std::to_string(location_1.getDevelopment() / 100) + "." + std::to_string(location_1.getDevelopment() % 100));
        float LocationViewDevelopment = (float)location_1.getDevelopment() / 100;
        
        LocationViewDisplayStrings[8] = ("Civilization: " + std::to_string(location_1.getCivilization() / 100) + "." + std::to_string(location_1.getCivilization() % 100));
        location_1.setCivilization(1055);
        float LocationViewCivilization = (float)location_1.getCivilization() / 100;

        LocationViewDisplayStrings[9] = ("Settlement: " + selectedSettlement->getName());
        LocationViewDisplayStrings[10] = ("Rank: " + rankNames.at(selectedSettlement->getRank()));
        LocationViewDisplayStrings[11] = ("Control: " + std::to_string(selectedSettlement->getControl() / 100) + "." + std::to_string(selectedSettlement->getControl() % 100));
        float LocationViewSettlementControl = (float)selectedSettlement->getControl() / 100;

        
        if (LocationViewActive) {
            LocationViewActive = !GuiWindowBox((Rectangle){ 4, 4, 420, 320 }, "");
            if (GuiTextBox((Rectangle){ 8, 32, 160, 30 }, LocationViewName, 128, LocationViewNameEditMode)) {
                LocationViewNameEditMode = !LocationViewNameEditMode;
                location_1.changeName(LocationViewName);
            }
            GuiGroupBox((Rectangle){172, 38, 144, 70}, "Population Info");
            GuiLabel((Rectangle){176, 38, 140, 30}, LocationViewDisplayStrings[0].c_str());
            GuiLabel((Rectangle){176, 52, 140, 30}, LocationViewDisplayStrings[1].c_str());
            GuiLabel((Rectangle){176, 66, 140, 30}, LocationViewDisplayStrings[2].c_str());
            GuiLabel((Rectangle){176, 80, 140, 30}, LocationViewDisplayStrings[3].c_str());
            
            GuiGroupBox((Rectangle){172, 118, 144, 106}, "Location Info");
            GuiLabel((Rectangle){176, 118, 140, 30}, LocationViewDisplayStrings[4].c_str());
            GuiLabel((Rectangle){176, 132, 140, 30}, LocationViewDisplayStrings[5].c_str());
            GuiLabel((Rectangle){176, 146, 140, 30}, LocationViewDisplayStrings[6].c_str());
            
            GuiLabel((Rectangle){176, 160, 140, 30}, LocationViewDisplayStrings[7].c_str());
            GuiProgressBar((Rectangle){174, 184, 140, 8}, NULL, NULL, &LocationViewDevelopment, 0, 100);
            GuiLabel((Rectangle){176, 188, 140, 30}, LocationViewDisplayStrings[8].c_str());
            GuiProgressBar((Rectangle){174, 212, 140, 8}, NULL, NULL, &LocationViewCivilization, 0, 100);
            
            GuiGroupBox((Rectangle){172, 234, 144, 90}, "Settlement Info");
            GuiLabel((Rectangle){176, 234, 140, 30}, LocationViewDisplayStrings[9].c_str());
            GuiLabel((Rectangle){176, 248, 140, 30}, LocationViewDisplayStrings[10].c_str());
            GuiLabel((Rectangle){176, 262, 140, 30}, LocationViewDisplayStrings[11].c_str());
            GuiProgressBar((Rectangle){174, 286, 140, 8}, NULL, NULL, &LocationViewSettlementControl, 0, 100);

            GuiScrollPanel(LocationViewScrollPanelBounds, 
                           "Settlements", 
                           LocationViewScrollPanelContent, 
                           &LocationViewScrollPanelScroll, 
                           &LocationViewScrollPanelView);

            BeginScissorMode(LocationViewScrollPanelView.x, 
                             LocationViewScrollPanelView.y, 
                             LocationViewScrollPanelView.width, 
                             LocationViewScrollPanelView.height);
                             
            drawButtons(LocationViewScrollPanelBounds, LocationViewScrollPanelScroll, &location_1, selectedSettlement);
                
            EndScissorMode();
        }
        else {
            LocationViewActive = GuiButton((Rectangle){ 4, 4, 240, 30 }, location_1.getName().c_str());
        }

        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
