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

    public:
        /**
         * @brief Parser constructor.
         * @param dataSet Value that corresponds to the dataset chosen.
         */
        Parser(bool dataSet);

        /**
         * Parses the data files and builds the graph.
         * @param graph Graph to be filled.
         */
        void readData(Graph* graph);

        /**
         * Setter for the dataSet to be read.
         * @param option Chooses the dataSet read.
         */
        void setCSV(bool option) { dataSetter = option; }
        bool getCSV() { return dataSetter; }
};


#endif //DA_PROJ1_PARSER_H
