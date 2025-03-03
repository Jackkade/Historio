#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <vector>
#include "Location.h"
#include "Pop.h"

class Pop;
class Location;

class Settlement {
public:
    Settlement(Location* l) : m_location{l} {};


    Location* getLocation() { return m_location; }

    void addPop(Pop* p);

    void update();

private:
    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;

};

#endif