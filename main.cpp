#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#include <iostream>
#include <map>
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raymath.h"

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

    Rectangle LocationViewBounds = {4, 4, 424, 454 };

    Rectangle LocationViewScrollPanelBounds = {8, 66, 160, 154};
    Rectangle LocationViewScrollPanelContent = {0, 0, 145, 600 };
    Rectangle LocationViewScrollPanelView = {0, 0, 0, 0};
    Vector2 LocationViewScrollPanelScroll = {0, 0};

    string LocationViewDisplayStrings[20];
    /*~~                    ~~*/


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Historio");

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    //ToggleFullscreen();
    

    GuiLoadStyle("ancien.rgs");
    Font font = LoadFont("resources/fonts/pixantiqua.png");
    GuiSetFont(font);

    //  Game Mechanics

    vector<vector<Location*>> locations;

    for(int i = 0; i < 10; i++) {
        locations.push_back(vector<Location*>{});
        for(int j = 0; j < 10; j++) {
            locations.at(i).push_back(new Location{Oceanic, Flat, Farmlands});
            locations.at(i).at(j)->changeName(std::to_string(i) + " " + std::to_string(j));
        }
    }

    locations.at(3).at(4)->changeClimate(Arctic);
    locations.at(2).at(5)->changeClimate(Arctic);
    locations.at(3).at(5)->changeVegetation(Barren);

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

    
    Location* selectedLocation = &location_1;
    Settlement* selectedSettlement = location_1.getCountryside();
    
    while(!WindowShouldClose()) {

        
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
            
        }
        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            Vector2 mousePos = GetMousePosition();
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(mousePos, camera);


            // Zoom increment
            // Uses log scaling to provide consistent zoom speed
            float scale = 0.2f*wheel;
            camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.5f, 8.0f);

            // Recalculate the camera's target after zooming
            // Get the world position under the mouse again after zoom change
            Vector2 mouseWorldPosAfterZoom = GetScreenToWorld2D(mousePos, camera);

            // Calculate the offset change caused by zooming
            Vector2 offsetChange = Vector2Subtract(mouseWorldPos, mouseWorldPosAfterZoom);

            // Adjust the camera target to keep the same world point under the mouse
            camera.target = Vector2Add(camera.target, offsetChange);
        }

        camera.target.x = Clamp(camera.target.x, -100, 1100 - SCREEN_WIDTH / camera.zoom);
        camera.target.y = Clamp(camera.target.y, -100, 1100 - SCREEN_HEIGHT / camera.zoom);
        
        

        /*//     Start Drawing Frame     //*/
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);


        /*//     Update Objects     //*/
        location_1.update();

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Vector2 selectionPos = GetScreenToWorld2D(GetMousePosition(),camera);
            
            if(
                (
                    !LocationViewActive 
                    || (LocationViewActive && !CheckCollisionPointRec(GetMousePosition(), (Rectangle){ 4, 4, 424, 454 }))
                ) 
                && CheckCollisionPointRec(selectionPos, (Rectangle){0,0,1000,1000})
            ) {
                Location* l = locations.at((int)selectionPos.x / 100).at((int)selectionPos.y / 100);
                selectedLocation = l; 
                selectedSettlement = selectedLocation->getCountryside();
                strncpy(LocationViewName, l->getName().c_str(), 128);
            }
        }


        /*//    Draw Map    //*/

        

        
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                
                DrawRectangle(
                    i*100, 
                    j*100, 
                    100, 
                    100, 
                    (Color){
                        (unsigned char)(locations.at(i).at(j)->getClimate() * 20), 
                        (unsigned char)(locations.at(i).at(j)->getTerrain() * 20 + i),
                        (unsigned char)(locations.at(i).at(j)->getVegetation() * 20 + j), 
                        255}
                );
            }
        }        
        EndMode2D();
        
        /*//     Draw User Interface (UI)     //*/
        //      Pop Info
        LocationViewDisplayStrings[0] = ("Population: " + std::to_string(selectedSettlement->getPopulation()));
        LocationViewDisplayStrings[1] = ("Unrest: " + std::to_string(selectedSettlement->getUnrest()));        
        LocationViewDisplayStrings[3] = ("SOL: " + std::to_string(selectedSettlement->getSOL()));
        
        //      Location Info
        LocationViewDisplayStrings[4] = ("Climate: " + climateNames.at(selectedLocation->getClimate()));
        LocationViewDisplayStrings[5] = ("Terrain: " + terrainNames.at(selectedLocation->getTerrain()));
        LocationViewDisplayStrings[6] = ("Vegetation: " + vegetationNames.at(selectedLocation->getVegetation()));

        LocationViewDisplayStrings[7] = ("Development: " + std::to_string(selectedLocation->getDevelopment() / 100) + "." + std::to_string(selectedLocation->getDevelopment() % 100));
        float LocationViewDevelopment = (float)selectedLocation->getDevelopment() / 100;
        
        LocationViewDisplayStrings[8] = ("Civilization: " + std::to_string(selectedLocation->getCivilization() / 100) + "." + std::to_string(selectedLocation->getCivilization() % 100));
        selectedLocation->setCivilization(1055);
        float LocationViewCivilization = (float)selectedLocation->getCivilization() / 100;

        LocationViewDisplayStrings[12] = ("Total Population: " + std::to_string(selectedLocation->getPopulation()));
        LocationViewDisplayStrings[13] = ("Total Food: " + std::to_string(selectedLocation->getFood()));
        LocationViewDisplayStrings[14] = ("Average SOL: " + std::to_string(selectedLocation->getSOL()));
        LocationViewDisplayStrings[15] = ("Average Unrest: " + std::to_string(selectedLocation->getUnrest()));
        LocationViewDisplayStrings[16] = ("Average Control: " + std::to_string(selectedLocation->getControl() / 100) + "." + std::to_string(selectedLocation->getControl() % 100));
        float LocationViewLocationAvgControl = (float)selectedLocation->getControl() / 100;

        //      Settlement Info
        LocationViewDisplayStrings[9] = ("Settlement: " + selectedSettlement->getName());
        LocationViewDisplayStrings[10] = ("Rank: " + rankNames.at(selectedSettlement->getRank()));
        LocationViewDisplayStrings[11] = ("Control: " + std::to_string(selectedSettlement->getControl() / 100) + "." + std::to_string(selectedSettlement->getControl() % 100));
        float LocationViewSettlementControl = (float)selectedSettlement->getControl() / 100;
        LocationViewDisplayStrings[2] = ("Average Unrest: " + std::to_string(selectedSettlement->getUnrest()));
        LocationViewDisplayStrings[17] = ("Average SOL: " + std::to_string(selectedSettlement->getSOL()));

        
        if (LocationViewActive) {
            LocationViewActive = !GuiWindowBox(LocationViewBounds, "");
            if (GuiTextBox((Rectangle){ 8, 32, 160, 30 }, LocationViewName, 128, LocationViewNameEditMode)) {
                LocationViewNameEditMode = !LocationViewNameEditMode;
                selectedLocation->changeName(LocationViewName);
            }
            GuiGroupBox((Rectangle){172, 38, 252, 200}, "Location Info");
            if (GuiLabelButton((Rectangle){176, 38, 140, 30}, LocationViewDisplayStrings[4].c_str())) {
                selectedLocation->changeClimate((Climate)((selectedLocation->getClimate() + 1) % 7));
            }
            
            if (GuiLabelButton((Rectangle){176, 52, 140, 30}, LocationViewDisplayStrings[5].c_str())) {
                selectedLocation->changeTerrain((Terrain)((selectedLocation->getTerrain() + 1) % 7));
            }
            if (GuiLabelButton((Rectangle){176, 66, 140, 30}, LocationViewDisplayStrings[6].c_str())) {
                selectedLocation->changeVegetation((Vegetation)((selectedLocation->getVegetation() + 1) % 7));
            }
            
            GuiLabel((Rectangle){176, 80, 140, 30}, LocationViewDisplayStrings[7].c_str());
            GuiProgressBar((Rectangle){174, 104, 140, 8}, NULL, NULL, &LocationViewDevelopment, 0, 100);
            GuiLabel((Rectangle){176, 108, 140, 30}, LocationViewDisplayStrings[8].c_str());
            GuiProgressBar((Rectangle){174, 132, 140, 8}, NULL, NULL, &LocationViewCivilization, 0, 100);

            GuiLabel((Rectangle){176, 136, 140, 30}, LocationViewDisplayStrings[12].c_str());
            GuiLabel((Rectangle){176, 150, 140, 30}, LocationViewDisplayStrings[13].c_str());
            GuiLabel((Rectangle){176, 164, 140, 30}, LocationViewDisplayStrings[14].c_str());
            GuiLabel((Rectangle){176, 178, 140, 30}, LocationViewDisplayStrings[15].c_str());
            GuiLabel((Rectangle){176, 192, 140, 30}, LocationViewDisplayStrings[16].c_str());
            GuiProgressBar((Rectangle){174, 216, 140, 8}, NULL, NULL, &LocationViewLocationAvgControl, 0, 100);

            
            float tempOffset = 130;
            GuiGroupBox((Rectangle){172, 118 + tempOffset, 252, 106}, "Settlement Info");
            GuiLabel((Rectangle){176, 118 + tempOffset, 140, 30}, LocationViewDisplayStrings[9].c_str());
            GuiLabel((Rectangle){176, 132 + tempOffset, 140, 30}, LocationViewDisplayStrings[10].c_str());
            GuiLabel((Rectangle){176, 146 + tempOffset, 140, 30}, LocationViewDisplayStrings[11].c_str());
            GuiProgressBar((Rectangle){174, 170 + tempOffset, 140, 8}, NULL, NULL, &LocationViewSettlementControl, 0, 100);
            GuiLabel((Rectangle){176, 174 + tempOffset, 140, 30}, LocationViewDisplayStrings[2].c_str());
            GuiLabel((Rectangle){176, 188 + tempOffset, 140, 30}, LocationViewDisplayStrings[17].c_str());
            
            
            GuiGroupBox((Rectangle){172, 234 + tempOffset, 252, 90}, "Population Info");
            GuiLabel((Rectangle){176, 234 + tempOffset, 140, 30}, LocationViewDisplayStrings[0].c_str());
            GuiLabel((Rectangle){176, 248 + tempOffset, 140, 30}, LocationViewDisplayStrings[1].c_str());
            GuiLabel((Rectangle){176, 262 + tempOffset, 140, 30}, LocationViewDisplayStrings[3].c_str());
            
            GuiScrollPanel(LocationViewScrollPanelBounds, 
                           "Settlements", 
                           LocationViewScrollPanelContent, 
                           &LocationViewScrollPanelScroll, 
                           &LocationViewScrollPanelView);

            BeginScissorMode(LocationViewScrollPanelView.x, 
                             LocationViewScrollPanelView.y, 
                             LocationViewScrollPanelView.width, 
                             LocationViewScrollPanelView.height);
                             
            drawButtons(LocationViewScrollPanelBounds, LocationViewScrollPanelScroll, selectedLocation, selectedSettlement);
                
            EndScissorMode();
        }
        else {
            LocationViewActive = GuiButton((Rectangle){ 4, 4, 240, 30 }, selectedLocation->getName().c_str());
        }


        /*//     Finish Drawing Frame     //*/
        EndDrawing();
    }
    CloseWindow();
}
