#include <iostream>
#include "Parser.h"
#include "Reservoir.h"
#include "City.h"

Parser::Parser(bool dataSetter) {
    this->dataSetter = dataSetter;
}

void Parser::readData() {

    std::ifstream inputFile;
    std::istringstream iss;
    std::string line;

    std::string name, code, id, demand, population,
    SA, SB, capacity, direction,
    reservoir, municipality, maxDelivery;

    switch (dataSetter) {
        case 0:
            csvIndicator = "/small";
            break;
        case 1:
            csvIndicator = "/large";
    }

    inputFile.open("../data/" + csvIndicator + "/Cities.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, name, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, demand, ',');
        getline(iss, population, '\r');

        graph->addCity(name, stoi(id), code, stoi(demand), 1000);
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Reservoirs.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, reservoir, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDelivery, ',');

        graph->addReservoir(reservoir, municipality, stoi(id), code, stoi(maxDelivery));
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Stations.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, id, ',');
        getline(iss, code, ',');

        if (!id.empty() && !code.empty())
            graph->addStation(code, stoi(id));
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Pipes.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, SA, ',');
        getline(iss, SB, ',');
        getline(iss, capacity, ',');
        getline(iss, direction, '\r');

        graph->addEdge(SA, SB, stoi(capacity));
    }

    inputFile.close();

    graph->printVertexSet();
}

