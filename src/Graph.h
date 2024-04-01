#ifndef DA_PROJ1_GRAPH_H
#define DA_PROJ1_GRAPH_H

#include "Vertex.h"
#include "Pipe.h"
#include <vector>
#include <limits>
#include <algorithm>

#define INF std::numeric_limits<double>::max();

class Graph {

protected:
    std::vector<Vertex*> vertexSet;
    void dfsVisit(Vertex *v,  std::vector<Vertex> & res) const;
public:
    Vertex* findVertex(const std::string &code) const;
    int getNumVertex() const;
    bool addCity(const std::string &name, const unsigned int &id,
                 const std::string &code, const unsigned int &demand, const unsigned int &population);
    bool addReservoir(const std::string &name, const std::string &municipality,
                             const unsigned int &id, const std::string &code, const unsigned int &max);
    bool addStation(const std::string &code, const unsigned int &id);
    bool removeVertex(const std::string &in);
    Pipe* addEdge(const std::string &sourc, const std::string &dest, double w);
    bool removeEdge(const std::string &sourc, const std::string &dest);
    std::vector<Vertex*> getVertexSet() const;
    void setVertexSet(std::vector<Vertex*> &v);
    std::vector<Vertex> dfs() const;
    std::vector<Vertex> dfs(const std::string & source) const;
    std::vector<Vertex> bfs(const std::string &source) const;
    void printVertexSet();

    bool addVertex(const std::string &code);

    void deleteEdge(const std::string &s, Pipe *pipe) const;

    void removeAllAdjEdges(Vertex *vertex);
};


#endif //DA_PROJ1_GRAPH_H
