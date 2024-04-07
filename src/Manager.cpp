#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>
#include <stack>
#include <unordered_set>
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
            cities.push_back(city);
        }
    }
    return cities;
}

City *Manager::getCity(std::string code) {
    for (auto* v : graph->getVertexSet()){
        if (v->getCode() == code) {
            return dynamic_cast<City*>(v);
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


void Manager::DFSPipeToCities(Vertex* v, std::unordered_set<City*>* visitedCities) {
    for (auto u : graph->getVertexSet()) {
        u->setVisited(false);
    }
    DFSPipeToCitiesVisit(v, visitedCities);
}

void Manager::DFSPipeToCitiesVisit(Vertex* v, std::unordered_set<City*>* visitedCities) {
    if (v->getCode()[0] == 'C') {
        visitedCities->insert(dynamic_cast<City*>(v));
        return;
    }
    v->setVisited(true);
    for (auto pipe : v->getAdj()) {
        if (!graph->findVertex(pipe->getDest())->isVisited()) {
            DFSPipeToCitiesVisit(graph->findVertex(pipe->getDest()), visitedCities);
        }
    }
}

void Manager::DFSPipeToReservoirs(Vertex* v, std::unordered_set<Reservoir*>* incomingReservoirs) {
    for (auto u : graph->getVertexSet()) {
        u->setVisited(false);
    }
    DFSPipeToReservoirsVisit(v, incomingReservoirs);
}

void Manager::DFSPipeToReservoirsVisit(Vertex* v, std::unordered_set<Reservoir*>* incomingReservoirs) {
    if (v->getCode()[0] == 'R') {
        incomingReservoirs->insert(dynamic_cast<Reservoir*>(v));
        return;
    }
    v->setVisited(true);
    for (auto pipe : v->getIncoming()) {
        if (!graph->findVertex(pipe->getOrig())->isVisited()) {
            DFSPipeToReservoirsVisit(graph->findVertex(pipe->getOrig()), incomingReservoirs);
        }
    }
}

void Manager::DFSReservoirToCities(Vertex* v, std::unordered_set<City*>* foundCities) {
    for (auto u : graph->getVertexSet()) {
        u->setVisited(false);
    }
    DFSReservoirToCitiesVisit(v, foundCities);
}

void Manager::DFSReservoirToCitiesVisit(Vertex* v, std::unordered_set<City*>* foundCities) {
    if (v->getCode()[0] == 'C') {
        foundCities->insert(dynamic_cast<City*>(v));
        return;
    }
    v->setVisited(true);
    for (auto pipe : v->getAdj()) {
        if (!graph->findVertex(pipe->getDest())->isVisited() && pipe->getFlow() != 0) {
            DFSPipeToCitiesVisit(graph->findVertex(pipe->getDest()), foundCities);
        }
    }
}

void Manager::findPathRC(Reservoir* r, City* c, std::stack<Pipe*>* path) {
    for (auto v : graph->getVertexSet()) {
        v->setVisited(false);
    }
    findPathRCVisit(r, c, path);
}

void Manager::findPathRCVisit(Vertex* v, City* c, std::stack<Pipe*>* path) {
    if (v->getCode()[0] == 'C') return;

    v->setVisited(true);
    std::vector<Pipe*> orderedPipes = v->getAdj();
    std::sort(orderedPipes.begin(), orderedPipes.end(), [](Pipe* a, Pipe* b) {return a->getWeight() - a->getFlow() > b->getWeight() - b->getFlow();});

    for (auto pipe : orderedPipes) {
        if (!graph->findVertex(pipe->getDest())->isVisited() && pipe->getFlow() != 0) {
            path->push(pipe);
            findPathRCVisit(graph->findVertex(pipe->getDest()), c, path);
            if (path->top()->getDest() == c->getCode()) return;
            path->pop();
        }
    }
}

void Manager::findPathREC(Reservoir* r, Pipe* pipe, City* c, std::stack<Pipe*>* path) {
    for (auto v : graph->getVertexSet()) {
        v->setVisited(false);
    }
    findPathREVisit(r, pipe, path);
    if (path->empty()) return;
    findPathECVisit(graph->findVertex(pipe->getDest()), c, path);
    if (path->top()->getDest() != c->getCode()) {
        while (!path->empty()) {
            path->pop();
        }
        return;
    }
}

void Manager::findPathREVisit(Vertex* v, Pipe* pipe, std::stack<Pipe*>* path) {
    if (v->getCode()[0] == 'C') return;

    v->setVisited(true);
    std::vector<Pipe*> orderedPipes = v->getAdj();
    std::sort(orderedPipes.begin(), orderedPipes.end(), [](Pipe* a, Pipe* b) {return a->getWeight() - a->getFlow() > b->getWeight() - b->getFlow();});

    for (auto p : orderedPipes) {
        if (!graph->findVertex(p->getDest())->isVisited() && pipe->getFlow() != 0) {
            path->push(pipe);
            if (path->top()->getDest() == pipe->getDest() && path->top()->getOrig() == pipe->getOrig()) return;
            findPathREVisit(graph->findVertex(pipe->getDest()), pipe, path);
            path->pop();
        }
    }
}

void Manager::findPathECVisit(Vertex* v, City* c, std::stack<Pipe*>* path) {
    if (v->getCode()[0] == 'C') return;

    v->setVisited(true);
    std::vector<Pipe*> orderedPipes = v->getAdj();
    std::sort(orderedPipes.begin(), orderedPipes.end(), [](Pipe* a, Pipe* b) {return a->getWeight() - a->getFlow() > b->getWeight() - b->getFlow();});

    for (auto pipe : orderedPipes) {
        if (!graph->findVertex(pipe->getDest())->isVisited() && pipe->getFlow() != 0) {
            path->push(pipe);
            findPathECVisit(graph->findVertex(pipe->getDest()), c, path);
            if (path->top()->getDest() == c->getCode()) return;
            path->pop();
        }
    }
}

void Manager::balanceWaterFlow() {
    std::queue<Pipe*> emptyPipes = {};
    for (auto v : graph->getVertexSet()) {
        for (auto p : v->getAdj()) {
            if (p->getFlow() == 0) {
                emptyPipes.push(p);
            }
        }
    }

    while (!emptyPipes.empty()) {
        Pipe* pipe = emptyPipes.front();
        emptyPipes.pop();
        if (pipe->getFlow() != 0) continue;

        std::unordered_set<City*> citiesReachedPipe = {};
        DFSPipeToCities(graph->findVertex(pipe->getDest()), &citiesReachedPipe);

        std::unordered_set<Reservoir*> reservoirsReachedPipe = {};
        DFSPipeToReservoirs(graph->findVertex(pipe->getDest()), &reservoirsReachedPipe);

        bool done = false;
        for (auto reservoir : reservoirsReachedPipe) {
            std::unordered_set<City*> cities = {};
            DFSReservoirToCities(reservoir, &cities);
            for (auto city : cities) {
                if (citiesReachedPipe.find(city) != citiesReachedPipe.end()) {
                    std::stack<Pipe*> path1 = {};
                    findPathRC(reservoir, city, &path1);
                    std::stack<Pipe*> path1Copy = path1;
                    int minFlow = INT_MAX;
                    while (!path1Copy.empty()) {
                        Pipe* pp = path1Copy.top();
                        if (pp->getFlow() < minFlow) minFlow = pp->getFlow();
                        path1Copy.pop();
                    }
                    path1Copy = path1;
                    minFlow /= 2;
                    while (!path1Copy.empty()) {
                        Pipe* pp = path1Copy.top();
                        pp->setFlow(pp->getFlow() - minFlow);
                        path1Copy.pop();
                    }

                    std::stack<Pipe*> path2 = {};
                    findPathREC(reservoir, pipe, city, &path2);
                    std::stack<Pipe*> path2Copy = path2;
                    int minCap = INT_MAX;
                    while (!path2Copy.empty()) {
                        Pipe* pp = path2Copy.top();
                        if (pp->getWeight() - pp->getFlow() < minCap) minCap = pp->getWeight() - pp->getFlow();
                        path2Copy.pop();
                    }
                    if (minCap >= minFlow) {
                        while (!path2.empty()) {
                            Pipe* pp = path2.top();
                            pp->setFlow(minFlow);
                            path2.pop();
                        }
                    } else {
                        int def = minFlow - minCap;
                        while (!path2.empty()) {
                            Pipe* pp = path2.top();
                            pp->setFlow(minCap);
                            path2.pop();
                        }
                        while (!path1.empty()) {
                            Pipe* pp = path1.top();
                            pp->setFlow(def);
                            path1.pop();
                        }
                    }
                    done = true;
                }
                if (done) break;
            }
        }
    }
}

void testAndVisit(std::queue< Vertex*> &q, Pipe *e, Vertex *w, double residual) {
    if (!w->isVisited() && residual > 0) {
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
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            if (g.findVertex(e->getDest()) != nullptr) {
                testAndVisit(q, e, g.findVertex(e->getDest()), e->getWeight() - e->getFlow());
            }
        }
        for (auto e: v->getIncoming()) {
            if (g.findVertex(e->getOrig()) != nullptr) {
                testAndVisit(q, e, g.findVertex(e->getOrig()), e->getFlow());
            }
        }
    }
    return t->isVisited();
}

double findMinResidualAlongPath(Graph* g, Vertex*s, Vertex *t) {
    double f = INF;
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
    return f;
}

void augmentFlowAlongPath(Graph* g, Vertex *s, Vertex *t, double f) {
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

    Vertex *superSource = new Vertex("SS");

    std::vector<Vertex*> vec = newGraph.getVertexSet();
    vec.push_back(superSource);
    newGraph.setVertexSet(vec);

    for (auto *v: newGraph.getVertexSet()) {
        if (v->getCode()[0] == 'R') {
            newGraph.addEdge("SS", v->getCode(), 999999999, 1);
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

        c->setIncome(std::min((unsigned int) maxFlow, c->getDemand()));
}

void Manager::addSuperVertexes() {
    graph->addVertex("SS");
    graph->addVertex("ST");

    for (Vertex* v : graph->getVertexSet()) {
        if (auto reservoir = dynamic_cast<Reservoir*>(v)) {
            graph->addEdge("SS", v->getCode(), reservoir->getMaxDelivery(), 1);
        }
        if (auto city = dynamic_cast<City*>(v)) {
            graph->addEdge(v->getCode(), "ST", city->getDemand(), 1);
            city->setIncome(0);
        }
    }
}

void Manager::computeCityFlow() {
    for (Vertex* vertex : graph->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            unsigned int flow = 0;
            for (const Pipe* pipe : vertex->getIncoming()) {
                flow += pipe->getFlow();
            }
            city->setIncome(flow);
        }
    }
}

void Manager::maxFlowAllCities() {
    addSuperVertexes();

    for (Vertex* v : graph->getVertexSet()) {
        for (Pipe* p : v->getAdj()) {
            p->setFlow(0);
        }
    }

    Vertex* superSource = graph->findVertex("SS");
    Vertex* superTarget = graph->findVertex("ST");

    while(findAugmentingPath(*graph, superSource, superTarget)) {
        double f = findMinResidualAlongPath(graph, superSource, superTarget);
        augmentFlowAlongPath(graph, superSource, superTarget, f);
    }

    computeCityFlow();
    graph->removeVertex("SS");
    graph->removeVertex("ST");
}

std::unordered_map<City*, unsigned int> Manager::checkReservoirFailure(std::string code) {
    std::unordered_map<Pipe*, double> weights;
    auto reservoir = dynamic_cast<Reservoir*>(graph->findVertex(code));

    std::unordered_map<City*, unsigned int> res;
    maxFlowAllCities();

    for (Vertex* vertex : graph->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            res.insert({city, city->getIncome()});
        }
    }

    for (Pipe* pipe : reservoir->getAdj()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    maxFlowAllCities();

    auto it = res.begin();
    while (it != res.end()) {
        if (it->second == it->first->getIncome())
            it = res.erase(it);
        else
            it++;
    }

    for (auto pair : weights) {
        pair.first->setWeight(pair.second);
    }

    return res;
}

std::unordered_map<City*, unsigned int> Manager::checkStationFailure(std::string code) {
    std::unordered_map<Pipe*, double> weights;
    auto station = dynamic_cast<Station*>(graph->findVertex(code));

    std::unordered_map<City*, unsigned int> res;
    maxFlowAllCities();

    for (Vertex* vertex : graph->getVertexSet()) {
        if (auto city = dynamic_cast<City*>(vertex)) {
            res.insert({city, city->getIncome()});
        }
    }

    for (Pipe* pipe : station->getAdj()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    for (Pipe *pipe: station->getIncoming()) {
        weights.insert({pipe, pipe->getWeight()});
        pipe->setWeight(0);
    }

    maxFlowAllCities();

    auto it = res.begin();
    while (it != res.end()) {
        if (it->second == it->first->getIncome())
            it = res.erase(it);
        else
            it++;
    }

    for (auto pair: weights) {
        pair.first->setWeight(pair.second);
    }

    return res;
}

Manager::Manager() : logger("../data/out/log.txt") {}

Logger* Manager::getLogger() {
    return &logger;
}

std::unordered_map<City*, unsigned int> Manager::checkPipeFailure(std::pair<std::string, std::string> vertices) {
    std::unordered_map<City*, unsigned int>  res = {};
    std::vector<std::pair<std::string, int>> start = {};

    maxFlowAllCities();

    for (auto v : graph->getVertexSet()) {
        if (v->getCode()[0] == 'C') {
            auto c = dynamic_cast<City *>(v);
            start.push_back(std::pair<std::string, int>(c->getCode(), c->getIncome()));
        }
    }

    auto v = graph->findVertex(vertices.first);
    Pipe* pipe = nullptr;
    for (auto p : v->getAdj()) {
        if (p->getDest() == vertices.second) {
            pipe = p;
            break;
        }
    }

    if (pipe == nullptr) {
        std::cout << "ERROR: Pipe not found.\n";
        return {};
    }

    int w = pipe->getWeight();
    pipe->setWeight(0);

    maxFlowAllCities();

    for (auto pair : start) {
        auto u = graph->findVertex(pair.first);
        auto c = dynamic_cast<City *>(u);
        if (pair.second > c->getIncome()) {
            res.insert({c, pair.second});
        }
    }

    pipe->setWeight(w);
    return res;
}

std::pair<City*, std::vector<Pipe*>> Manager::checkVitalPipes(std::string code) {
    std::vector<Pipe*> res = {};
    std::queue<Pipe*> pipeQ = {};

    maxFlowAllCities();
    int defaultFlow = dynamic_cast<City *>(graph->findVertex(code))->getIncome();

    for (auto v: graph->getVertexSet()) {
        for (auto e: v->getAdj()) {
            pipeQ.push(e);
        }
    }

    while (!pipeQ.empty()) {
        Pipe *p = pipeQ.front();
        pipeQ.pop();
        int w = p->getWeight();
        p->setWeight(0);
        maxFlowAllCities();
        if (dynamic_cast<City*>(graph->findVertex(code))->getIncome() != defaultFlow) {
            res.push_back(p);

        }
        p->setWeight(w);
    }

    return {dynamic_cast<City *>(graph->findVertex(code)), res};
}

metrics Manager::networkMetrics() {

    int countPipes = 0;
    double totalDifference = 0.0;
    double squaredDifferenceSum = 0.0;
    int maxDifference = INT_MIN;

    for (auto* v : graph->getVertexSet()) {
        for (auto* p : v->getAdj()) {

                int difference = abs(p->getWeight() - p->getFlow());
                totalDifference += difference;
                squaredDifferenceSum += difference * difference;
                if (difference > maxDifference  && p->getDirection() == 1) {
                    maxDifference = difference;

            }
            countPipes++;
        }
    }

    double averageDifference = totalDifference / countPipes;

    double variance = ((squaredDifferenceSum - countPipes * (averageDifference*averageDifference))/( countPipes - 1));

    return {averageDifference, variance, maxDifference};
}

void Manager::resetGraph() {
    delete graph;
    this->graph = new Graph();
}
