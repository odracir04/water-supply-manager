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