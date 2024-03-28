#include <iostream>
#include "Graph.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"

Vertex* Graph::findVertex(const std::string &code) const {
    for (Vertex* vertex : vertexSet) {
        if (vertex->getCode() == code) {
            return vertex;
        }
    }
    return nullptr;
}

bool Graph::addCity(const std::string &name, const unsigned int &id,
                    const std::string &code, const unsigned int &demand, const unsigned int &population) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new City(name, id, code, demand, population));
    return true;
}

bool Graph::addReservoir(const std::string &name, const std::string &municipality,
                         const unsigned int &id, const std::string &code, const unsigned int &max) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Reservoir(name, municipality, id, code, max));
    return true;
}

bool Graph::addStation(const std::string &code, const unsigned int &id) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Station(id, code));
    return true;
}

void Graph::printVertexSet() {
    for(auto v : vertexSet ){
        std::cout << v->getCode() << "\n";
    }
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

bool Graph::addEdge(const std::string &sourc, const std::string &dest, double w) {
    Vertex* source = findVertex(sourc);
    Vertex* destination = findVertex(dest);

    if (source == nullptr || destination == nullptr)
        return false;

    source->addPipe(dest, w);
    return true;
}
