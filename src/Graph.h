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
    /**
     * Searches for the vertex code in vertex set.
     * @param code Code of the vertex.
     * @return Corresponding Vertex if it finds the code in the vertex set, nullptr otherwise.
     * Complexity: O(v), where v in the number of vertexes in vertex set.
     */
    Vertex* findVertex(const std::string &code) const;
    int getNumVertex() const;

    /**
     * Adds the city to the vertex set after verifying that it already exists.
     * @param name Name of the city.
     * @param id Id of the city.
     * @param code Code of the city.
     * @param demand Demand of the city.
     * @param population Population of the city.
     * @return True if added successfully, False otherwise.
     */
    bool addCity(const std::string &name, const unsigned int &id,
                 const std::string &code, const unsigned int &demand, const unsigned int &population);
    /**
     * Adds the reservoir to the vertex set after verifying that it already exists.
     * @param name Name of the reservoir.
     * @param municipality Municipality of the reservoir.
     * @param id Id of the reservoir.
     * @param code Code of the reservoir.
     * @param max MaxDelivery of the reservoir.
     * @return True if added successfully, False otherwise.
     */
    bool addReservoir(const std::string &name, const std::string &municipality,
                             const unsigned int &id, const std::string &code, const unsigned int &max);

    /**
     * Adds the station to the vertex set after verifying that it already exists.
     * @param code Code of the station.
     * @param id Id of the station.
     * @return True if added successfully, False otherwise.
     */
    bool addStation(const std::string &code, const unsigned int &id);

    /**
     * Removes the vertex from the vertex set, his adjacent pipes and his incoming pipes.
     * @param in Code of the vertex to be removed.
     * @return True if successfully removed, False otherwise.
     */
    bool removeVertex(const std::string &in);

    /**
     * Adds a pipe connecting tow vertexes, checks if the vertexes exists first.
     * @param sourc Source vertex.
     * @param dest Destination vertex.
     * @param w Weight of the pipe.
     * @param direction Direction of the edge
     * @return The new pipe created or nullptr if one of the vertexes not found.
     */
    Pipe* addEdge(const std::string &sourc, const std::string &dest, double w, bool direction);

    /**
     * Removes an pipe connecting two vertexes.
     * @param sourc Source vertex.
     * @param dest Destinnation vertex.
     * @return True if successfully remover, False otherwise.
     */
    bool removeEdge(const std::string &sourc, const std::string &dest);

    /**
     * Getter for the VertexSet.
     * @return Vector of Vertexes corresponding to the VertexSet.
     */
    std::vector<Vertex*> getVertexSet() const;

    /**
     * Setter for the VertexSet
     * @param v The new vector of vertexes to be set as the VertexSet
     */
    void setVertexSet(std::vector<Vertex*> &v);
    std::vector<Vertex> dfs() const;
    std::vector<Vertex> dfs(const std::string & source) const;
    std::vector<Vertex> bfs(const std::string &source) const;
    void printVertexSet();

    /**
     * Adds a new Vertex to the Vertex Set verifying if it already exists.
     * @param code Code of the Vertex to be removed.
     * @return True if it successfully removes, False otherwise.
     */
    bool addVertex(const std::string &code);

    /**
     * Removes all incoming pipes.
     * @param s Vertex code.
     * @param pipe
     */
    void deleteEdge(const std::string &s, Pipe *pipe) const;

    void removeAllAdjEdges(Vertex *vertex);
};


#endif //DA_PROJ1_GRAPH_H
