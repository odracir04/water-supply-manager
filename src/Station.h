#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>
#include "Vertex.h"

class Station : public Vertex {
    private:
        unsigned int id;

    public:
        /**
        * @brief Station constructor.
        * @param i Id of the station.
        * @param c Code of the station.
        */
        Station(unsigned int i, std::string c) : id(i), Vertex(c) {}

        /**
         * Station getter.
         * @return id of the station.
         */
        unsigned int getId() const {return this->id;}
};


#endif //DA_PROJ1_STATION_H
