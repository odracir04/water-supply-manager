#ifndef DA_PROJ1_RESERVOIR_H
#define DA_PROJ1_RESERVOIR_H

#include <string>
#include "Vertex.h"

class Reservoir : public Vertex {
    private:
        std::string name;
        std::string municipality;
        unsigned int id;
        unsigned int maxDelivery;
    public:
        Reservoir(std::string n, std::string m, unsigned int i, std::string c, unsigned int max);

    std::string getName() const {return this->name;}
    std::string getMunicipality() const {return this->municipality;}
    unsigned int getId() const {return this->id;}
    unsigned int getMaxDelivery() const {return this->maxDelivery;}


    void setName(std::string const n) {this->name = n;}
    void setMunicipality(std::string const m) {this->municipality = m;}
    void setMaxDelivery(unsigned int const max) {this->maxDelivery = max;}

};


#endif //DA_PROJ1_RESERVOIR_H
