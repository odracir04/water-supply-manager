
#include <iostream>
#include "Parser.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"

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
        waterNetwork.addVertex(new City(stoi(id), code, name, stoi(demand), 10000));
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
        getline(iss, maxDelivery, '\r');

        waterNetwork.addVertex(new Reservoir(reservoir, municipality, stoi(id), code, stoi(maxDelivery)));
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Stations.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, id, ',');
        getline(iss, code, ',');

        if (id.empty() || code.empty()) continue;

        waterNetwork.addVertex(new Station(stoi(id), code));
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

        Node src(0, SA);
        Node dest(0, SB);

        if (stoi(direction) == 1)
            waterNetwork.addEdge(&src, &dest, stoi(capacity));
        else if (stoi(direction) == 0)
            waterNetwork.addBidirectionalEdge(&src, &dest, stoi(capacity));
    }

    inputFile.close();
}

