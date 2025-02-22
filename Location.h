#ifndef LOCATION_H
#define LOCATION_H
#include "Terrain.h"

class Location {
public:
    void changeTerrain(Terrain t);
    void changeVegetation(Vegetation v);
    void changeClimate(Climate c);
private:
    Climate m_climate;
    Terrain m_terrain;
    Vegetation m_vegetation;
    //Owner
    //Climate, Terrain, Vegetation
    //Neighbors
    //Settlements
    //Countryside
};

#endif