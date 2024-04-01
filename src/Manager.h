#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H


#include "Graph.h"
#include "Parser.h"
#include "City.h"

class Manager {

private:
    Graph *graph = new Graph;
    Parser parser = Parser(false);

    void computeCityFlow();
    void addSuperVertexes();

public:
    void extractFiles(bool option);
    void maxFlowCities(std::string dest);
    void maxFlowAll();

    bool checkNetworkRequirements();
    void balanceWaterFlow();
    std::vector<City*> checkReservoirFailure(std::string code);
    std::vector<City*> checkStationFailure(std::string code);
    void checkPipeFailure(std::pair<std::string, std::string> vertices);
    void checkVitalPipes(std::string code);
    std::vector<City*> getCities();

    void maxFlowAllCities();

    City* getCity(std::string code);

    bool validateStation(std::string code);
    bool validateCity(std::string code);
    bool validateReservoir(std::string code);
    bool validatePipe(std::string src, std::string dest);

    void resetGraph();
};


#endif //DA_PROJ1_MANAGER_H
