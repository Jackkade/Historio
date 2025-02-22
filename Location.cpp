#include "Location.h"


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