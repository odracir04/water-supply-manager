
#include "Vertex.h"

Vertex::Vertex(std::string code) : code(code){}

std::string Vertex::getCode() const {
    return code;
}

void Vertex::addPipe(const std::string &dest, const int &w) {
    adj.push_back(Pipe(dest, w));
}



