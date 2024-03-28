//
// Created by ricardo on 3/20/24.
//

#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H


#include "Graph.h"
#include "Parser.h"
#include "City.h"
#include "Logger.h"

class Manager {

private:
    Logger logger;
    Graph *graph = new Graph;
    Parser parser = Parser(false);

public:
    Manager();
    void extractFiles(bool option);
    void maxFlowCities(std::string dest);
    void maxFlowAll();

    bool checkNetworkRequirements();
    void balanceWaterFlow();
    void checkReservoirFailure(std::string code);
    void checkStationFailure(std::string code);
    void checkPipeFailure(std::pair<std::string, std::string> vertices);
    std::vector<City*> getCities();

    City* getCity(std::string code);

    bool validateStation(std::string code);
    bool validateCity(std::string code);
    bool validateReservoir(std::string code);
    bool validatePipe(std::string src, std::string dest);

    Logger* getLogger();
};


#endif //DA_PROJ1_MANAGER_H
