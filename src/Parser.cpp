
#include <iostream>
#include "Parser.h"

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


        std::cout << name << " "<< population<<"\n";
        //tempCounter++;
        //Adding here to Graph
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



        std::cout << SA << " "<< direction<<"\n";

        //Adding here to Graph
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Reservoir.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, reservoir, ',');
        getline(iss, municipality, ',');
        getline(iss, id, ',');
        getline(iss, code, ',');
        getline(iss, maxDelivery, '\r');



        std::cout << reservoir << " "<< municipality<<"\n";

        //Adding here to Graph
    }

    inputFile.close();

    inputFile.open("../data/" + csvIndicator + "/Stations.csv");

    getline(inputFile, line);
    while(getline(inputFile, line)){
        iss.clear();
        iss.str(line);

        getline(iss, id, ',');
        getline(iss, code, '\r');


        std::cout << id << " "<< code<<"\n";
        tempCounter++;
        //Adding here to Graph
    }

    inputFile.close();


}

