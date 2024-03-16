#ifndef DA_PROJ1_PARSER_H
#define DA_PROJ1_PARSER_H

#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"
#include "Node.h"


class Parser {
    private:
        bool dataSetter;
        std::string csvIndicator;

    public:
        Parser(bool dataSet);
        void readData(); //Graph
        Graph<Node*> waterNetwork;
};


#endif //DA_PROJ1_PARSER_H
