

#ifndef DA_PROJ1_GRAPH_H
#define DA_PROJ1_GRAPH_H
#include "Vertex.h"
#include "Pipe.h"


class Graph {
    std::vector<Vertex*> vertexSet;    // vertex set
    void dfsVisit(Vertex *v,  std::vector<Vertex> & res) const;
public:
    Vertex *findVertex(const  std::string &in) const;
    int getNumVertex() const;
    bool addVertex(const Vertex* v);
    bool removeVertex(const std::string &in);
    bool addEdge(const std::string &sourc, const std::string &dest, double w);
    bool removeEdge(const std::string &sourc, const std::string &dest);
    std::vector<Vertex * > getVertexSet() const;
    std::vector<Vertex> dfs() const;
    std::vector<Vertex> dfs(const std::string & source) const;
    std::vector<Vertex> bfs(const std::string &source) const;
    void printVertexSet();

    void emitDOTFile(std::string gname);

};


#endif //DA_PROJ1_GRAPH_H
