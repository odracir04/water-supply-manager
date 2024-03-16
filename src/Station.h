#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>
#include "Node.h"

class Station : public Node {
    public:
        Station(unsigned int i, std::string c) : Node(i, c) {};
};


#endif //DA_PROJ1_STATION_H
