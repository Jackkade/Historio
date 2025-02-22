#ifndef LOCATION_H
#define LOCATION_H
#include "Terrain.h"

class Location {
public:

    Location(Climate c, Terrain t, Vegetation v) : m_climate(c), m_terrain(t), m_vegetation(v) {}

    Climate getClimate() { return m_climate; }
    Terrain getTerrain() { return m_terrain; }
    Vegetation getVegetation() { return m_vegetation; }

    void changeTerrain(Terrain t);
    void changeVegetation(Vegetation v);
    void changeClimate(Climate c);
private:
    //Need to add names
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