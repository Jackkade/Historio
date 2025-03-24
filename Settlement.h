#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <vector>
#include "Types.h"
#include "Pop.h"


class Settlement {
public:
    Settlement(Location* l) : m_location{l} {};
    ~Settlement();


    Location* getLocation() { return m_location; }

    void addPop(Pop* p);

    void update();

private:
    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;

};

#endif