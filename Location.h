#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include "Terrain.h"
#include "Settlement.h"

class Settlement;

class Location {
public:

    Location(Climate c, Terrain t, Vegetation v);

    ~Location() { //Delete Internal Countryside Settlement
        delete m_countryside;
    }

    unsigned int getID() { return m_id; }
    std::string getName() { return m_name; }
    Climate getClimate() { return m_climate; }
    Terrain getTerrain() { return m_terrain; }
    Vegetation getVegetation() { return m_vegetation; }


    void changeName(std::string s);
    void changeTerrain(Terrain t);
    void changeVegetation(Vegetation v);
    void changeClimate(Climate c);
private:
    unsigned int m_id;
    static unsigned int m_provIds;
    std::string m_name;
    //Climate, Terrain, Vegetation
    Climate m_climate;
    Terrain m_terrain;
    Vegetation m_vegetation;
    //Owner
    //Neighbors
    //Settlements
    std::vector<Settlement> m_settlements;
    //Countryside
    Settlement* m_countryside = nullptr;
};

#endif