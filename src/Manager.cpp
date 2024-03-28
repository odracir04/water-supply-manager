//
// Created by ricardo on 3/20/24.
//

#include <iostream>
#include <queue>
#include <cfloat>
#include "Manager.h"
#include "City.h"

void Manager::extractFiles(bool option) {
    parser.setCSV(option);
    parser.readData(graph);
}

std::vector<City*> Manager::getCities() {
    std::vector<City*> cities;
    for (auto* v : graph->getVertexSet()){
        if (City* city = dynamic_cast<City*>(v)) {
            cities.push_back(city); // Call city specific method
        }
    }
    return cities;
}

City *Manager::getCity(std::string code) {
    for (auto* v : graph->getVertexSet()){
        if (v->getCode() == code) {
            return dynamic_cast<City*>(v); // Call city specific method
        }
    }

    return nullptr;
}

bool Manager::validateStation(std::string code) {
    return true;
}

bool Manager::validateCity(std::string code) {
    return true;
}

bool Manager::validateReservoir(std::string code) {
    return true;
}

bool Manager::validatePipe(std::string src, std::string dest) {
    return true;
}

void Manager::balanceWaterFlow() {

}
void testAndVisit(std::queue< Vertex*> &q, Pipe *e, Vertex *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (!w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool findAugmentingPath(Graph &g, Vertex* s ,Vertex* t) {
    for (auto *v: g.getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
// BFS to find an augmenting path
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for (auto e: v->getAdj()) {
            if (g.findVertex(e->getDest()) != nullptr) {
                testAndVisit(q, e, g.findVertex(e->getDest()), e->getWeight() - e->getFlow());
            }
        }
// Process incoming edges
        for (auto e: v->getIncoming()) {
            if (g.findVertex(e->getOrig()) != nullptr) {
                testAndVisit(q, e, g.findVertex(e->getOrig()), e->getFlow());
            }
        }
// Return true if a path to the target is found, false otherwise
    }
    return t->isVisited();
}

double findMinResidualAlongPath(Graph* g, Vertex*s, Vertex *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (g->findVertex(e->getDest()) == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = g->findVertex(e->getOrig());
        }
        else {
            f = std::min(f, e->getFlow());
            v = g->findVertex(e->getDest());
        }
    }
// Return the minimum residual capacity
    return f;
}

void augmentFlowAlongPath(Graph* g, Vertex *s, Vertex *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (g->findVertex(e->getDest()) == v) {
            e->setFlow(flow + f);
            v = g->findVertex(e->getOrig());
        } else {
            e->setFlow(flow - f);
            v = g->findVertex(e->getDest());
        }
    }
}

    void Manager::maxFlowCities(std::string dest) {


        Graph newGraph = *graph;

        Vertex *t = newGraph.findVertex(dest);

        if (t == nullptr) {
            std::cout << "Invalid  target!";
            return;
        }

        //Create super Source
        Vertex *superSource = new Vertex("SS");

        std::vector<Vertex*> vec = newGraph.getVertexSet();
        vec.push_back(superSource);
        newGraph.setVertexSet(vec);

        for (auto *v: newGraph.getVertexSet()) {
            if (v->getCode()[0] == 'R') {
                newGraph.addEdge("SS", v->getCode(), 999999999);
            }
        }


        for (auto v: newGraph.getVertexSet()) {
            for (auto *e: v->getAdj()) {
                e->setFlow(0);
            }
        }

        double maxFlow = 0;
        while (findAugmentingPath(newGraph, superSource, t)) {
            double f = findMinResidualAlongPath(&newGraph,superSource, t);
            augmentFlowAlongPath(&newGraph,superSource, t, f);
            maxFlow += f;
        }

        //newGraph.removeAllAdjEdges(superSource);

        for(auto* v : newGraph.getVertexSet()){
            if(v->getCode() == "SS"){
                delete v;
            }
        }
        newGraph.getVertexSet().clear();
        std::vector<Vertex*> temp = graph->getVertexSet();
        newGraph.setVertexSet(temp);

        *graph = newGraph;


        City*  c = dynamic_cast<City *>(graph->findVertex(dest));
        c->setIncome(maxFlow);
    }

void Manager::maxFlowAll() {
    for(auto* v : graph->getVertexSet()){
        if(v->getCode()[0] == 'C'){
            maxFlowCities(v->getCode());
        }
    }
}



void Manager::checkReservoirFailure(std::string code) {

    }

    void Manager::checkStationFailure(std::string code) {

    }

    void Manager::checkPipeFailure(std::pair<std::string, std::string> vertices) {

    }

    bool Manager::checkNetworkRequirements() {
        return true;
    }

Manager::Manager() : logger("../out/log.txt") {}

Logger* Manager::getLogger() {
    return &logger;
}

