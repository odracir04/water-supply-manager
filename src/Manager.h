#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H


#include "Graph.h"
#include "Parser.h"
#include "City.h"
#include "Logger.h"

struct metrics {
    double average;
    double variance;
    int max_difference;
};

class Manager {

private:
    Logger logger;
    Graph *graph = new Graph;
    Parser parser = Parser(false);


    /**
    * Calculates the total flow of each city based on incoming pipes and sets the income accordingly.
    * Complexity: O(C + P), where C is the number of cities and P is the number of pipes leading to cities.
    * Note: If the number of incoming pipes for each city is a constant, the complexity becomes O(C).
    */
    void computeCityFlow();

    /**
    * Adds super vertices 'SS' and 'ST' to the graph and connects them to reservoirs and cities
    * respectively, forming a super source and super sink that are key for flow algorithms correctness.
    * Complexity: O(V), where V is the number of vertices in the graph.
    */
    void addSuperVertexes();

public:
    /**
     * Manager constructor.
     * Builds a logger instance indicating output file location.
     */
    Manager();

    /**
     * Calls parser functions that reads the data files according to the dataset chosen and builds the graph.
     * @param option Dataset choice.
     */
    void extractFiles(bool option);

    /**
     * Calculates the maximum flow from a super source 'SS' to the destination(dest) city.
     * Complexity: O(V * P^2) where V is the number of vertexes and P the number of pipes in the graph.
     * @param dest Destination City.
     */
    void maxFlowCities(std::string dest);

    void balanceWaterFlow();

    /**
     * Simulates Reservoir failure by setting the weights of the adjacent pipes to 0
     * and then recalculates the maximum flow to all cities identifying the cities affected by that change.
     * Complexity: O(V * P^2) where V is the number of vertexes and P the number of pipes.
     * @param code Code of the Reservoir to simulate.
     * @return The cities affected by the Reservoir failure.
     */
    std::unordered_map<City*, unsigned int>  checkReservoirFailure(std::string code);

    /**
     * Simulates Station failure by setting the weights of the adjacent pipes to 0
     * and then recalculates the maximum flow to all cities identifying the cities affected by that change.
     * Complexity: O(V * P^2) where V is the number of vertexes and P the number of pipes.
     * @param code Code of the Station to simulate.
     * @return The cities affected by the Station failure.
     */
    std::unordered_map<City*, unsigned int> checkStationFailure(std::string code);

    /**
     * Simulates specific Pipe failure by setting the weight of that to 0
     * and then recalculates the maximum flow to all cities identifying the cities affected by that change.
     * Complexity: O(V * P^2) where V is the number of vertexes and P the number of pipes.
     * @param vertices A pair of vertexes representing the endpoints of the pipe to be simulated.
     * @return The cities affected by Pipe failure.
     */
    std::unordered_map<City*, unsigned int>  checkPipeFailure(std::pair<std::string, std::string> vertices);

    /**
     * Identifies vital pipes connected to a single city by simulating the failure of each pipe individually
     * recalculating the maximum flow to all cities and checking changes in the income.
     * Complexity: O(V * P^3) where V is the number of vertexes and P the number of pipes.
     * @param code Code of the city to be simulated
     * @return Pair containing the city tested and a vector of the vital pipes calculated.
     */
    std::pair<City*, std::vector<Pipe*>> checkVitalPipes(std::string code);

    /**
     * Getter for all cities in the Vertex Set of the Graph.
     * Complexity: O(V) where V is the number of vertexes.
     * @return Vector of all cities in the graph.
     */
    std::vector<City*> getCities();

    /**
     * Computes the maximum flow to all cities in the graph using the Edmonds-Karp Algorithm.
     * * O(V * P^2), where V is the number of vertices and P is the number of pipes in the graph.
     */
    void maxFlowAllCities();


    /**
     * Getter for a specific city based on the code.
     * Searches in the Vertex set for a specific city.
     * Complexity: O(V) where V is the number of vertexes.
     * @param code Code of the city.
     * @return Corresponding City object.
     */
    City* getCity(std::string code);

    /**
     * Validates whether a Station with a given code exists in the graph.
     * Complexity: O(V) where V is the number of vertexes.
     * @param code Code of the station to be tested.
     * @return True if the station exits, False otherwise.
     */
    bool validateStation(std::string code);

    /**
    * Validates whether a City with a given code exists in the graph.
    * Complexity: O(V) where V is the number of vertexes.
    * @param code Code of the city to be tested.
    * @return True if the city exits, False otherwise.
    */
    bool validateCity(std::string code);

    /**
    * Validates whether a Reservoir with a given code exists in the graph.
    * Complexity: O(V) where V is the number of vertexes.
    * @param code Code of the reservoir to be tested.
    * @return True if the reservoir exits, False otherwise.
    */
    bool validateReservoir(std::string code);

    /**
    * Validates whether a Pipe with a given source and destination exists.
    * Complexity: O(V) where V is the number of vertexes.
    * @param src Pipe source code.
    * @param dest Pipe destination code.
    * @return True if the Pipe exits, False otherwise.
    */
    bool validatePipe(std::string src, std::string dest);

    /**
     * Logger Getter.
     * @return The instance of the Logger object.
     */
    Logger* getLogger();

    /**
     * Resets the graph by deleting the existing graph object and creating a new empty graph.
     */
    void resetGraph();

    /**
     * Computes some metrics, such as the average and variance of the differences
     * between capacity and flow for each pipe, as well as the maximum difference.
     * @return A struct containing the network metrics.
     * Complexity: O(V + P) where V is the number of vertexes and P the number of pipes.
     */
    metrics networkMetrics();
};


#endif //DA_PROJ1_MANAGER_H
