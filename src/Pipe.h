
#ifndef DA_PROJ1_PIPE_H
#define DA_PROJ1_PIPE_H

#include <string>


class Pipe {
    private:
        std::string servicePointB;
        int capacity;
    public:
        Pipe(std::string d, int w);
        std::string *getDest() const;
        void setDest(std::string *dest);
        double getWeight() const;
        void setWeight(double weight);


};


#endif //DA_PROJ1_PIPE_H
