#include "Pop.h"

Pop::Pop(Settlement& l) {
    setSettlement(l);
}

Pop::Pop(unsigned int population, Settlement& l) {
    setSettlement(l);
    addPopulation(population - 1);
}

void Pop::update() {
    if(m_settlement->getLocation()->getClimate() == Temperate) {
        m_population += 10;
    }
    else {
        if (m_population % 10 == 0) {
            m_unrest += 1;
        }
        m_population += 1;
    }
}

void Pop::setSettlement(Settlement& l) {
    //TODO: remove from old settlement
    m_settlement = &l;
    l.addPop(this);
}


void Pop::addPopulation(int a) {
    m_population += a;
    if(m_population < 1) {
        //This should destroy the pop, but for now just set it to one
        m_population = 1;
    }
    //No upper bound currently
}

void Pop::addUnrest(int a) {
    m_unrest += a;
    if(m_unrest < -100) {
        m_unrest = -100;
    }
    else if (m_unrest > 100) {
        m_unrest = 100;
    }
}

void Pop::addSOL(int a) {
    m_sol += a;
    if (m_sol < 0) {
        m_sol = 0;
    }
    else if (m_sol > 100) {
        m_sol = 100;
    }
}