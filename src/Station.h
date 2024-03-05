#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

#include <string>

class Station {
    private:
        unsigned int id;
        std::string code;
    public:
        Station(unsigned int i, std::string c) : id(i), code(c) {}

        unsigned int getId() const {return this->id;}
        std::string getCode() const {return this->code;}

        /*
        void setId(unsigned int const i) {this->id = i;}
        void setCode(std::string const c) {this->code = c;}
         */
};


#endif //DA_PROJ1_STATION_H
