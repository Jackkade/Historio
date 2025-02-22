#include "Pop.h"

Pop::Pop(unsigned int population) {
    addPopulation(population - 1);
}

Pop::Pop(unsigned int population, Location& l) {
    setLocation(l);
    addPopulation(population - 1);
}

void Pop::update() {
    if(m_location->getClimate() == Temperate) {
        m_population += 10;
    }
    else {
        if (m_population % 10 == 0) {
            m_unrest += 1;
        }
        m_population += 1;
    }
}

void Pop::setLocation(Location& l) {
    m_location = &l;
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

void Pop::addFood(int a) {
    m_sol += a;
    if (m_food < 0) {
        m_food = 0;
    }
    else if (m_food > 100) {
        m_food = 100;
    }
}