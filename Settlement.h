#ifndef SETTLEMENT_H
#define SETTLEMENT_H
#include <string>
#include <vector>
#include "Types.h"
#include "Ranks.h"
#include "Pop.h"


class Settlement {
public:
    Settlement(Location* l);
    ~Settlement();


    void setID(unsigned int i) { m_id = i; }    //WARNING!! IF YOU ARE USING THIS, YOU ARE DOING SOMETHING WRONG
    void addPop(Pop* p);
    void changeName(std::string s);
    
    void update();
    
    /*~~~~~~*/
    int getID() { return m_id; }
    int getPopulation();
    unsigned int getFood() { return m_food; }
    unsigned int getControl() { return m_control; } 
    std::string getName() { return m_name; }
    Rank getRank();
    Location* getLocation() { return m_location; }

    //Setters
    void setRank(Rank r);
    void addFood(int a);

private:
    unsigned int m_id = 0;
    std::string m_name;
    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;
    Rank m_rank = Community;
    //  Int represented as Decimal between 0.00 <-> 100.00 
    //  When Printing this, divide by 100 first
    unsigned int m_control = 5000; 
    
    // Number of physical food 'tokens' i.e. some amount of calories that are stored in the location and eaten by pops
    unsigned int m_food = 0;        
};

#endif