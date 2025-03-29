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


    
    void addPop(Pop* p);
    void changeName(std::string s);
    
    void update();
    
    /*~~~~~~*/
    
    int getPopulation(); 
    string getName() { return m_name; }
    Rank getRank();
    Location* getLocation() { return m_location; }

    //Setters
    void setRank(Rank r);

private:
    unsigned int m_id;
    std::string m_name;

    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;
    Rank m_rank = Community;
    //  Int represented as Decimal between 0.00 <-> 100.00 
    //  When Printing this, divide by 100 first
    unsigned int m_control = 5000; 

};

#endif