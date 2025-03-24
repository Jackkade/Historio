#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <vector>
#include "Types.h"
#include "Ranks.h"
#include "Pop.h"


class Settlement {
public:
    Settlement(Location* l);
    ~Settlement();


    Location* getLocation() { return m_location; }

    void addPop(Pop* p);

    void update();

    /*~~~~~~*/

    int getPopulation(); 

    Rank getRank();

    //Setters
    void setRank(Rank r);

private:
    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;
    Rank m_rank = Community;
    //  Int represented as Decimal between 0.00 <-> 100.00 
    //  When Printing this, divide by 100 first
    unsigned int m_control = 5000; 

};

#endif