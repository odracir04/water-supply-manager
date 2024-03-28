#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>
#include "Vertex.h"

class Station : public Vertex {
    private:
        unsigned int id;

    public:
        Station(unsigned int i, std::string c) : id(i), Vertex(c) {}

        unsigned int getId() const {return this->id;}
        /*
        void setId(unsigned int const i) {this->id = i;}
        void setCode(std::string const c) {this->code = c;}
         */
};


#endif //DA_PROJ1_STATION_H
