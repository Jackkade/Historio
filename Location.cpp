#include "Location.h"

unsigned int Location::m_provIds = 0;

Location::Location(Climate c, Terrain t, Vegetation v) : m_climate(c), m_terrain(t), m_vegetation(v) {
    m_id = m_provIds;
    m_provIds++;
    m_countryside = new Settlement(this);
    m_countryside->setRank(Camp);
}

Location::~Location() {
    delete m_countryside;
}

void Location::update() {
    //Handle Settlements
    if(m_countryside) {
        m_countryside->update();
    }
    for(Settlement* s : m_settlements) {
        s->update();
    }

    //Handle Location
    if(m_civilization > 10000) {
        m_civilization = 10000;
    }
    if(m_development > 10000) {
        m_development = 10000;
    }
}

void Location::changeName(std::string s) {
    if(!s.empty()) {
        m_name = s;
    }
}

void Location::changeTerrain(Terrain t) {
    m_terrain = t;
}
void Location::changeVegetation(Vegetation v) {
    m_vegetation = v;
}
void Location::changeClimate(Climate c) {
    m_climate = c;
}

void Location::setCivilization(int i) {
    if (i > 10000) {
        m_civilization = 10000;
    }
    else if ( i < 0 ) {
        m_civilization = 0;
    }
    else {
        m_civilization = i;
    }
}

void Location::setDevelopment(int i) {
    if (i > 10000) {
        m_development = 10000;
    }
    else if ( i < 0 ) {
        m_development = 0;
    }
    else {
        m_development = i;
    }
}
int Location::getPopulation() {
    int rt = m_countryside->getPopulation();

    for(Settlement* s : m_settlements) {
        rt += s->getPopulation();
    }

    return rt;
}

void Location::addSettlement(Settlement* s) {
    s->setID(m_settlements.size());
    m_settlements.push_back(s);
}
