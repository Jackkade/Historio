#include "Settlement.h"

Settlement::Settlement(Location *l) {
    m_location = l;
    l->addSettlement(*this);
}

Settlement::~Settlement()
{
}

void Settlement::addPop(Pop *p)
{
    m_pops.push_back(p);
}

void Settlement::update() {

    for(int i = 0; i < m_pops.size(); i++) {
        m_pops.at(i)->update();
    }

}

int Settlement::getPopulation() {
    
    int rt = 0;
    for (Pop* p : m_pops) {
        rt += p->getPopulation();    
    }
    return rt;
}
