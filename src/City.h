#ifndef DA_PROJ1_CITY_H
#define DA_PROJ1_CITY_H

#include <string>
#include "Node.h"

class City : public Node {
    private:
        std::string name;
        unsigned int demand;
        unsigned int population;
    public:
        City(unsigned int id, std::string code, std::string n, unsigned int d,
             unsigned int p) : Node(id, code), name(n), demand(d), population(p) {}

    std::string getName() const {return this->name;}
    unsigned int getDemand() const {return this->demand;}
    unsigned int getPopulation() const {return this->population;}


    void setName(std::string const n) {this->name = n;}
    void setDemand(unsigned int const d) {this->demand = d;}
    void setPopulation(unsigned int const p) {this->population = p;}

};


#endif //DA_PROJ1_CITY_H
