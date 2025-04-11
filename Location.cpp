#include "Location.h"

unsigned int Location::m_provIds = 0;

Location::Location(Climate c, Terrain t, Vegetation v) : m_climate(c), m_terrain(t), m_vegetation(v) {
    m_id = m_provIds;
    m_provIds++;
    m_countryside = new Settlement(this);
    m_countryside->setRank(Camp);
    m_countryside->changeName(m_name);
}

Location::~Location() {
    delete m_countryside;
}

void Location::update() {
    //Handle Settlements
    if(m_countryside) {
        m_countryside->update();
    }
    for(int i = 0; i < getSettlementAmount(); i++) {
        m_settlements.at(i)->update();
    }

    //Handle Location
    if(m_civilization > 10000) {
        m_civilization = 10000;
    }
    if(m_development > 10000) {
        m_development = 10000;
    }
}

Settlement *Location::getSettlement(int id)
{
    return m_settlements.at(id);
}

void Location::changeName(std::string s)
{
    if(!s.empty()) {
        m_name = s;
        m_countryside->changeName(s);
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

int Location::getUnrest()
{
    int rt = m_countryside->getUnrest();
    int i = 0;
    for(Settlement* s : m_settlements) {
        rt += s->getUnrest();
        i++;
    }

    if(i > 0) {
        return rt / i; //Return average Unrest
    }
    else {
        return 0;
    }
}

unsigned int Location::getSOL()
{
    int rt = m_countryside->getSOL();
    int i = 0;
    for(Settlement* s : m_settlements) {
        rt += s->getSOL();
        i++;
    }

    if(i > 0) {
        return rt / i; //Return average SOL
    }
    else {
        return 0;
    }
}

unsigned int Location::getFood()
{
    int rt = m_countryside->getFood();

    for(Settlement* s : m_settlements) {
        rt += s->getFood();
    }

    return rt;
}

void Location::addSettlement(Settlement* s) {
    s->setID(m_settlements.size());
    m_settlements.push_back(s);
}
