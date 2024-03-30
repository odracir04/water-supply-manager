//
// Created by ricardo on 3/20/24.
//

#include <iostream>
#include <queue>
#include <cfloat>
#include <unordered_map>
#include <unordered_set>
#include <climits>
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
    if (code.size() < 4 || code.substr(0, 3) != "PS_")
        return false;

    return graph->findVertex(code);
}

bool Manager::validateCity(std::string code) {
    if (code.size() < 3 || code.substr(0, 2) != "C_")
        return false;

    return graph->findVertex(code);
}

bool Manager::validateReservoir(std::string code) {
    if (code.size() < 3 || code.substr(0, 2) != "R_")
        return false;

    return graph->findVertex(code);
}

bool Manager::validatePipe(std::string src, std::string dest) {
    if (!validateReservoir(src) && !validateStation(src)) return false;
    if (!validateStation(dest) && !validateCity(dest)) return false;

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

void Manager::clearVertexes() {
    for (Vertex* vertex : graph->getVertexSet()) {
        vertex->setVisited(false);
        vertex->setPath(nullptr);
    }
}

void Manager::computePath(Vertex* src, Vertex* dest) {
    std::queue<Vertex*> processing;
    processing.push(src);

    while (!processing.empty()) {
        Vertex* current = processing.front();
        if (current->getCode() == dest->getCode()) return;
        for (Pipe* pipe : current->getAdj()) {
            Vertex* next = graph->findVertex(pipe->getDest());
            if (pipe->getFlow() < pipe->getWeight() && !next->isVisited()) {
                next->setPath(pipe);
                processing.push(next);
            }
        }
        current->setVisited(true);
        processing.pop();
    }
}

void Manager::dubiousMaxFlow(Graph* g) {
    std::vector<std::pair<std::string, std::string>> extraEdges;
    std::unordered_set<Pipe*> back_edges;

    g->addVertex("SS");
    g->addVertex("ST");

    for (Vertex* v : g->getVertexSet()) {
        if (auto reservoir = dynamic_cast<Reservoir*>(v)) {
            g->addEdge("SS", v->getCode(), reservoir->getMaxDelivery());
            extraEdges.push_back({"SS", v->getCode()});
        }
        if (auto city = dynamic_cast<City*>(v)) {
            g->addEdge(v->getCode(), "ST", city->getDemand());
            city->setIncome(0);
            extraEdges.push_back({v->getCode(), "ST"});
        }
    }

    clearVertexes();

    for (Vertex* vertex : g->getVertexSet()) {
        for (Pipe *pipe: vertex->getAdj()) {
            pipe->setReverse(nullptr);
        }
    }

    for (Vertex* vertex : g->getVertexSet()) {
        for (Pipe* pipe: vertex->getAdj()) {
            if (pipe->getReverse() == nullptr) {
                pipe->setFlow(0);

                Pipe *reverse = graph->addEdge(pipe->getDest(), pipe->getOrig(), pipe->getWeight());

                reverse->setFlow(reverse->getWeight());
                pipe->setReverse(reverse);
                reverse->setReverse(pipe);
                back_edges.insert(reverse);
            }
        }
    }

    Vertex* superSource = g->findVertex("SS");
    Vertex* superTarget = g->findVertex("ST");

    computePath( superSource, superTarget);

    Pipe* backtrack = superTarget->getPath();

    while (backtrack != nullptr) {

        double max_flow = INT_MAX;
        while (backtrack != nullptr) {
            max_flow = std::min(max_flow, backtrack->getWeight() - backtrack->getFlow());
            backtrack = graph->findVertex(backtrack->getOrig())->getPath();
        }

        backtrack = superTarget->getPath();
        while (backtrack != nullptr) {
            backtrack->setFlow(backtrack->getFlow() + max_flow);
            backtrack->getReverse()->setFlow(backtrack->getReverse()->getFlow() - max_flow);
            backtrack = graph->findVertex(backtrack->getOrig())->getPath();
        }

        clearVertexes();
        computePath( superSource, superTarget);
        backtrack = superTarget->getPath();
    }

    for (auto edge : extraEdges) {
        g->removeEdge(edge.first, edge.second);
    }

    for (Pipe* edge : back_edges) {
        g->removeEdge(edge);
    }

    for (Vertex* vertex : g->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            unsigned int flow = 0;
            for (const Pipe* pipe : vertex->getIncoming()) {
                flow += pipe->getFlow();
            }
            city->setIncome(flow);
        }
    }
}

std::vector<City*> Manager::checkReservoirFailure(std::string code) {
    std::unordered_map<Pipe*, double> weights;
    auto reservoir = dynamic_cast<Reservoir*>(graph->findVertex(code));

    for (Pipe* pipe : reservoir->getAdj()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    dubiousMaxFlow(graph);

    std::vector<City*> res;
    for (Vertex* vertex : graph->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            if (city->getDemand() > city->getIncome())
                res.push_back(city);
        }
    }

    for (auto pair : weights) {
        pair.first->setWeight(pair.second);
    }

    return res;
}

std::vector<City*> Manager::checkStationFailure(std::string code) {
    std::unordered_map<Pipe*, double> weights;
    auto station = dynamic_cast<Station*>(graph->findVertex(code));

    for (Pipe* pipe : station->getAdj()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    for (Pipe* pipe : station->getIncoming()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    dubiousMaxFlow(graph);

    std::vector<City*> res;
    for (Vertex* vertex : graph->getVertexSet()) {
        if (auto city = dynamic_cast<City *>(vertex)) {
            if (city->getDemand() > city->getIncome())
                res.push_back(city);
        }
    }

    for (auto pair : weights) {
        pair.first->setWeight(pair.second);
    }

    return res;
}

    void Manager::checkPipeFailure(std::pair<std::string, std::string> vertices) {

    }

    bool Manager::checkNetworkRequirements() {
        return true;
    }

void Manager::resetGraph() {
    delete graph;
    this->graph = new Graph();
}