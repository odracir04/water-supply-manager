#ifndef DA_PROJ1_PARSER_H
#define DA_PROJ1_PARSER_H

#include <string>
#include <sstream>
#include <fstream>


class Parser {
    private:
        bool dataSetter;
        std::string csvIndicator;

    public:
        Parser(bool dataSet);
        void readData(); //Graph
};


#endif //DA_PROJ1_PARSER_H
