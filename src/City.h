#ifndef DA_PROJ1_CITY_H
#define DA_PROJ1_CITY_H

#include <string>

class City  {
    private:
        std::string name;
        unsigned int id;
        std::string code;
        unsigned int demand;
        unsigned int population;
    public:
        City(std::string n, unsigned int i, std::string c, unsigned int d, unsigned int p) : name(n), id(i), code(c), demand(d), population(p) {}

    std::string getName() const {return this->name;}
    unsigned int getId() const {return this->id;}
    std::string getCode() const {return this->code;}
    unsigned int getDemand() const {return this->demand;}
    unsigned int getPopulation() const {return this->population;}

    /*
    void setName(std::string const n) {this->name = n;}
    void setId(unsigned int const i) {this->id = i;}
    void setCode(std::string const c) {this->code = c;}
    void setDemand(unsigned int const d) {this->demand = d;}
    void setPopulation(unsigned int const p) {this->population = p;}
    */
};


#endif //DA_PROJ1_CITY_H
