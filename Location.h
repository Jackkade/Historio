#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include "Terrain.h"

class Location {
public:

    Location(Climate c, Terrain t, Vegetation v) : m_climate(c), m_terrain(t), m_vegetation(v) {}

    std::string getName() { return m_name; }
    Climate getClimate() { return m_climate; }
    Terrain getTerrain() { return m_terrain; }
    Vegetation getVegetation() { return m_vegetation; }


    void changeName(std::string s);
    void changeTerrain(Terrain t);
    void changeVegetation(Vegetation v);
    void changeClimate(Climate c);
private:
    std::string m_name;
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