#include "Pipe.h"

Pipe::Pipe(const std::string &s, const std::string &d, double &w, bool direction) {
    this->servicePointA = s;
    this->servicePointB = d;
    this->capacity = w;
    this->direction = direction;
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

void Pipe::setWeight(double weight) {
    this->capacity = weight;
}

Pipe *Pipe::getReverse() const {
    return reverse;
}

void Pipe::setReverse(Pipe *pipe) {
    this->reverse = pipe;
}

bool Pipe::getDirection() {
    return direction;
}
