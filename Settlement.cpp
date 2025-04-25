#include "Settlement.h"

Settlement::Settlement(Location *l) {
    m_location = l;
    l->addSettlement(this);
}
Settlement::Settlement(Location *l, bool b) {
    m_location = l;
    //l->addSettlement(this);
}

Settlement::~Settlement()
{
}

void Settlement::addPop(Pop *p)
{
    m_pops.push_back(p);
}

void Settlement::changeName(std::string s) {
    if(!s.empty()) {
        m_name = s;
    }
}

void Settlement::update() {

    if(m_control > 10000) {
        m_control = 10000; 
    }
    for(Pop* p : m_pops) {
        p->update();
    }

}

int Settlement::getPopulation() {
    
    int rt = 0;
    for (Pop* p : m_pops) {
        rt += p->getPopulation();    
    }
    return rt;
}

Rank Settlement::getRank() {
    return m_rank;
}

int Settlement::getUnrest() {
    int rt = 0;
    int i = 0;
    for (Pop* p : m_pops) {
        rt += p->getUnrest();    
        i++;
    }

    if(i > 0) {
        return rt / i; //Return average unrest
    }
    else {
        return 0;
    }
}

unsigned int Settlement::getSOL() {
    int rt = 0;
    int i = 0;
    for (Pop* p : m_pops) {
        rt += p->getSOL();    
        i++;
    }

    if(i > 0) {
        return rt / i; //Return average SOL
    }
    else {
        return 0;
    }
}

void Settlement::setRank(Rank r) {
    m_rank = r;
}

void Settlement::addFood(int a) {
    m_food += a;
    if (m_food < 0) {
        m_food = 0;
    }
}