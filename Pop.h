#ifndef POP_H
#define POP_H
#include "Settlement.h"
#include "Location.h"

class Location;
class Settlement;

class Pop {
public:
    //Constructors
    Pop() = default;                                //Default Attributes
    Pop(unsigned int population);                   //Default with Pop
    Pop(unsigned int population, Settlement& l);      //With Pop, in Settlement

    //TODO: once reference are added, make constructors require pointers
    
    //Updaters
    void update();

    //Mutators
    void addPopulation(int a);
    void addUnrest(int a);
    void addSOL(int a);
    void addFood(int a);
    void setSettlement(Settlement& l);

    //Getters
    unsigned int getPopulation() { return m_population; }
    int getUnrest() { return m_unrest; }
    unsigned int getSOL() { return m_sol; }
    
private:
    // Internal Attributes of pops, no need to reference others.
    unsigned int m_population = 1;  //Population
    int m_unrest = 0;               //Average unrest in Pop
    unsigned int m_sol = 0;         //Standard of Living
    unsigned int m_food = 0;        //Percent of Food Availability

    // External Attributes, references to other objects
                                    //Relgion
                                    //Culture
                                    //Language
    // Relations
                                    //Loyalty
    Settlement* m_settlement = nullptr;
                                    //Job
};

#endif