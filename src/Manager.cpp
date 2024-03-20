//
// Created by ricardo on 3/20/24.
//

#include "Manager.h"
#include "City.h"

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

void Manager::maxFlowCities() {

}

void Manager::checkReservoirFailure(std::string code) {

}

void Manager::checkStationFailure(std::string code) {

}

void Manager::checkPipeFailure(std::pair<std::string, std::string> vertices) {

}

bool Manager::checkNetworkRequirements() {
    return true;
}
