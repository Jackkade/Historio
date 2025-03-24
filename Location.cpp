#include "Location.h"

unsigned int Location::m_provIds = 0;

Location::Location(Climate c, Terrain t, Vegetation v) : m_climate(c), m_terrain(t), m_vegetation(v) {
    m_id = m_provIds;
    m_provIds++;
    m_countryside = new Settlement(this);
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