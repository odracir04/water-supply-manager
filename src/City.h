#ifndef DA_PROJ1_CITY_H
#define DA_PROJ1_CITY_H

#include <string>
#include "Vertex.h"

class City : public Vertex {
    private:
        std::string name;
        unsigned int id;
        unsigned int demand;
        unsigned int population;
        unsigned int supplied = 0;
    public:
        City(std::string n, unsigned int i, std::string c, unsigned int d, unsigned int p)
        : Vertex(c), name(n), id(i), demand(d), population(p) {}

    std::string getName() const {return this->name;}
    unsigned int getId() const {return this->id;}
    unsigned int getDemand() const {return this->demand;}
    unsigned int getPopulation() const {return this->population;}
    unsigned int getSupplied() const { return this->supplied; }

    /*
    void setName(std::string const n) {this->name = n;}
    void setId(unsigned int const i) {this->id = i;}
    void setCode(std::string const c) {this->code = c;}
    void setDemand(unsigned int const d) {this->demand = d;}
    void setPopulation(unsigned int const p) {this->population = p;}
    */
    void setSupplied(unsigned int s) { this->supplied = s; }
};


#endif //DA_PROJ1_CITY_H
