
#include "Vertex.h"

Vertex::Vertex(std::string code) : code(code){}

std::string Vertex::getCode() const {
    return code;
}


const std::vector<Pipe *> &Vertex::getAdj() const {
    return this->adj;
}

Pipe *Vertex::getPath() const {
    return path;
}

void Vertex::setPath(Pipe *path) {
    this->path = path;
}

std::vector<Pipe *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::setVisited(bool v) {
    this->visited = v;
}

bool Vertex::isVisited() const {
    return visited;
}
