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

bool Graph::addVertex(const std::string &code) {
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(code));
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

Pipe* Graph::addEdge(const std::string &sourc, const std::string &dest, double w, bool direction) {
    Vertex* source = findVertex(sourc);
    Vertex* destination = findVertex(dest);

    if (source == nullptr || destination == nullptr)
        return nullptr;

    auto newPipe = new Pipe(sourc, dest, w, direction );
    source->adj.push_back(newPipe);
    destination->incoming.push_back(newPipe);
    return newPipe;
}

void Graph::setVertexSet(std::vector<Vertex *> &v) {
    this->vertexSet = v;
}

void Graph::deleteEdge(const std::string &s, Pipe *pipe) const{
    Vertex *dest = findVertex(pipe->getDest());
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        auto* temp = findVertex((*it)->getOrig());
        if (temp->getCode() == s) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete pipe;
}

bool Graph::removeEdge(const std::string &sourc, const std::string &dest) {
    bool removedEdge = false;

    Vertex* s = findVertex(sourc);
    Vertex* t = findVertex(dest);

    if(s == nullptr || t == nullptr){
        std::cout << "Invalid!";
        return removedEdge;
    }

    auto it = s->adj.begin();
    while (it != s->adj.end()) {
        Pipe *p = *it;
        Vertex *tempDest = findVertex(p->getDest());
        if (tempDest->getCode() == dest) {
            it = s->adj.erase(it);
            deleteEdge(sourc, p);
            removedEdge = true;
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

void Graph::removeAllAdjEdges(Vertex* vertex) {
    for (auto & it : vertex->adj) {
        delete it;
    }
    vertex->adj.clear();
}

bool Graph::removeVertex(const std::string &in) {
    auto it = vertexSet.begin();

    while (it != vertexSet.end() && (*it) != findVertex(in)) it++;

    if (it == vertexSet.end()) return false;

    Vertex* vertex = *it;

    while (!vertex->adj.empty()) {
        Pipe* pipe = vertex->adj[0];
        removeEdge(pipe->getOrig(), pipe->getDest());
    }

    while (!vertex->incoming.empty()) {
        Pipe* pipe = vertex->incoming[0];
        removeEdge(pipe->getOrig(), pipe->getDest());
    }

    vertexSet.erase(it);
    delete vertex;

    return true;
}

