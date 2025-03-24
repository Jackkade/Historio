#include "Settlement.h"

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
