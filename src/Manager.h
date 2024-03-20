//
// Created by ricardo on 3/20/24.
//

#ifndef DA_PROJ1_MANAGER_H
#define DA_PROJ1_MANAGER_H


#include "Graph.h"
#include "Parser.h"
#include "City.h"

class Manager {

private:
    Graph *graph = new Graph;
    Parser parser = Parser(false);

public:
    void extractFiles(bool option);
    void maxFlowCities();
    void balanceWaterFlow();
    void checkReservoirFailure();
    void checkStationFailure();
    void checkPipeFailure();
    std::vector<City*> getCities();
};


#endif //DA_PROJ1_MANAGER_H
