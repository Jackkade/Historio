#include <vector>
#include "Location.h"
#include "Pop.h"

class Settlement {
public:

    void addPop(Pop* p);
private:
    Location* m_location = nullptr;
    std::vector<Pop*> m_pops;

};