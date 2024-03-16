#include <iostream>
#include "Graph.h"
Vertex * Graph::findVertex(const std::string &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

bool Graph::addVertex(const Vertex* v) {
    if ( findVertex(v->getInfo()) != NULL)
        return false;
    vertexSet.push_back(new Vertex(v->getInfo()));
    return true;
}

void Graph::printVertexSet() {
    for(auto v : vertexSet ){
        std::cout << v->getInfo() << "\n";
    }
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}
