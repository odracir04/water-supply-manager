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

    /**
     * @brief Reservoir constructor.
     * @param n Name of the reservoir.
     * @param m Municipality of the reservoir.
     * @param i Id of the reservoir.
     * @param c Code of the reservoir.
     * @param max Max Delivery of the reservoir
     */
    Reservoir(std::string n, std::string m, unsigned int i, std::string c, unsigned int max);

    /**
     * Reservoir name getter.
     * @return name of the city.
     */
    std::string getName() const {return this->name;}

    /**
     * Reservoir municipality getter.
     * @return municipality of the city.
     */
    std::string getMunicipality() const {return this->municipality;}

    /**
     * Reservoir id getter.
     * @return id of the city.
     */
    unsigned int getId() const {return this->id;}

    /**
     * Reservoir Max Delivery getter.
     * @return maxDelivery of the city.
     */
    unsigned int getMaxDelivery() const {return this->maxDelivery;}

    /*
    void setName(std::string const n) {this->name = n;}
    void setMunicipality(std::string const m) {this->municipality = m;}
    void setId(unsigned int i) {this->id = i;}
    void setCode(std::string const c) {this->code = c;}
    void setMaxDelivery(unsigned int const max) {this->maxDelivery = max;}
    */
};


#endif //DA_PROJ1_RESERVOIR_H
