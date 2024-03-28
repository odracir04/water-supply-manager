//
// Created by ricardo on 3/20/24.
//

#include <iostream>
#include <queue>
#include <cfloat>
#include "Manager.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"

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
            std::cout << "Invalid target!";
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
    /*for(auto* v : graph->getVertexSet()){
        if(v->getCode()[0] == 'C'){
            maxFlowCities(v->getCode());
        }
    }*/
    dubiousMaxFlow(graph);
}

void Manager::dubiousMaxFlow(Graph* g) {

    g->addVertex("SS");
    g->addVertex("ST");

    for (Vertex* v : g->getVertexSet()) {
        if (auto reservoir = dynamic_cast<Reservoir*>(v)) {
            g->addEdge("SS", v->getCode(), reservoir->getMaxDelivery());
        }
        if (auto city = dynamic_cast<City*>(v)) {
            g->addEdge(v->getCode(), "ST", city->getDemand());
        }
    }

    for (Vertex* v : g->getVertexSet()) {
        for (Pipe* p : v->getAdj()) {
            p->setFlow(0);
        }
    }

    Vertex* superSource = g->findVertex("SS");
    Vertex* superTarget = g->findVertex("ST");

    while(findAugmentingPath(*g, superSource, superTarget)) {
        double f = findMinResidualAlongPath(g, superSource, superTarget);
        augmentFlowAlongPath(g, superSource, superTarget, f);
    }

    for (Vertex* vertex : g->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            unsigned int flow = 0;
            for (const Pipe* pipe : vertex->getAdj()) {
                flow += pipe->getFlow();
            }
            city->setIncome(flow);
        }
    }
}

std::vector<City*> Manager::checkReservoirFailure(std::string code) {
    Graph* newGraph(graph);
    auto reservoir = dynamic_cast<Reservoir*>(newGraph->findVertex(code));

    for (Pipe* pipe : reservoir->getAdj()) {
        pipe->setWeight(0);
    }

    dubiousMaxFlow(newGraph);

    std::vector<City*> res;
    for (Vertex* vertex : newGraph->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            if (city->getDemand() > city->getIncome())
                res.push_back(city);
        }
    }

    return res;
}

std::vector<City*> Manager::checkStationFailure(std::string code) {
    Graph* newGraph(graph);
    auto station = dynamic_cast<Station*>(newGraph->findVertex(code));

    for (Pipe* pipe : station->getAdj()) {
        pipe->setWeight(0);
    }

    for (Pipe* pipe : station->getIncoming()) {
        pipe->setWeight(0);
    }

    dubiousMaxFlow(newGraph);

    std::vector<City*> res;
    for (Vertex* vertex : newGraph->getVertexSet()) {
        if (auto city = dynamic_cast<City *>(vertex)) {
            if (city->getDemand() > city->getIncome())
                res.push_back(city);
        }
    }

    return res;
}

    void Manager::checkPipeFailure(std::pair<std::string, std::string> vertices) {

    }

    bool Manager::checkNetworkRequirements() {
        return true;
    }

