#include "Settlement.h"

Settlement::Settlement(Location *l) {
    m_location = l;
    l->addSettlement(this);
}

Settlement::~Settlement()
{
}

void Settlement::addPop(Pop *p)
{
    m_pops.push_back(p);
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

void Settlement::setRank(Rank r) {
    m_rank = r;
}
