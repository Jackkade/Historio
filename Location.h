#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include "Types.h"
#include "Terrain.h"
#include "Settlement.h"

class Location {
public:

    Location(Climate c, Terrain t, Vegetation v);

    ~Location();

    void update();

    //Attribute Getters

    unsigned int getID() { return m_id; }
    std::string getName() { return m_name; }
    Climate getClimate() { return m_climate; }
    Terrain getTerrain() { return m_terrain; }
    Vegetation getVegetation() { return m_vegetation; }
    unsigned int getCivilization() { return m_civilization; }
    unsigned int getDevelopment() { return m_development; }

    // Relationship Getters

    Settlement* getSettlement(int id);
    Settlement* getCountryside() { return m_countryside; }

    //Attribute Setters

    void changeName(std::string s);
    void changeTerrain(Terrain t);
    void changeVegetation(Vegetation v);
    void changeClimate(Climate c);

    void setCivilization(int i);
    void setDevelopment(int i);

    /*------------------*/

    //Relationship getters

    int getPopulation(); 
    int getSettlementAmount() { return m_settlements.size(); }

    //Relationship Setters

    void addSettlement(Settlement* s);

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
    std::vector<Settlement*> m_settlements;
    //Countryside
    Settlement* m_countryside = nullptr;

    //Gov Attributes
    
    //  Int represented as Decimal between 0.00 <-> 100.00 
    //  When Printing this, divide by 100 first
    unsigned int m_civilization = 0; 
    //  Int represented as Decimal between 0.00 <-> 100.00 
    //  When Printing this, divide by 100 first
    unsigned int m_development = 0; 

};

#endif