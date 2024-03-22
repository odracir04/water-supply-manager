
#include "Pipe.h"

Pipe::Pipe(const std::string &s, const std::string &d, double &w) {
    this->servicePointA = s;
    this->servicePointB = d;
    this->capacity = w;
}

double Pipe::getFlow() const {
    return flow;
}

void Pipe::setFlow(double f) {
    this->flow = f;
}

std::string Pipe::getDest() const {
    return servicePointB;
}

void Pipe::setDest(std::string *dest) {
    this->servicePointB = *dest;
}

std::string Pipe::getOrig() const {
    return servicePointA;
}

double Pipe::getWeight() const {
    return capacity;
}
