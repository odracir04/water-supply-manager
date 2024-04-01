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
        double income;
    public:

    /**
     * @brief City constructor.
     * @param n Name of the city.
     * @param i Id of the city.
     * @param c Code of the city.
     * @param d Demand of the city
     * @param p Population of the city.
     */
    City(std::string n, unsigned int i, std::string c, unsigned int d, unsigned int p)
    : Vertex(c), name(n), id(i), demand(d), population(p) {}

    /**
     * City name getter.
     * @return name of the city.
     */
    std::string getName() const {return this->name;}

    /**
     * City id getter.
     * @return if of the city.
     */
    unsigned int getId() const {return this->id;}

    /**
     * City demand getter.
     * @return demand of the city.
     */
    unsigned int getDemand() const {return this->demand;}

    /**
     * City Income getter.
     * @return income of the city.
     */
    double getIncome() const{ return income;}

    /**
     * City income setter.
     * @return
     */
    void setIncome(double inc){this->income=inc;}

    /**
     * City Population getter.
     * @return population of the city.
     */
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
