
#ifndef DA_PROJ1_PIPE_H
#define DA_PROJ1_PIPE_H

#include <string>


class Pipe {
    private:
        std::string servicePointA;
        std::string servicePointB;
        int capacity;
        double flow;
    public:
        Pipe(const std::string &s, const std::string &d, double &w);
        double getFlow() const;
        void setFlow(double f);

        std::string getDest() const;
        std::string getOrig() const;

        void setDest(std::string *dest);
        double getWeight() const;
        void setWeight(double weight);


};


#endif //DA_PROJ1_PIPE_H
