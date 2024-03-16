#ifndef DA_PROJ1_PARSER_H
#define DA_PROJ1_PARSER_H

#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"


class Parser {
    private:
        bool dataSetter;
        std::string csvIndicator;
        Graph *graph;

    public:
        Parser(bool dataSet);
        void readData(); //Graph
};


#endif //DA_PROJ1_PARSER_H
