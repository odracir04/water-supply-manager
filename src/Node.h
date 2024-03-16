//
// Created by ricardo on 3/13/24.
//

#ifndef DA_PROJ1_NODE_H
#define DA_PROJ1_NODE_H

#include <string>

class Node {
private:
    unsigned int id;
    std::string code;

public:
    Node(unsigned int id_, std::string code_) : id(id_), code(code_) {};
    unsigned int getId() const {return this->id;}
    std::string getCode() const {return this->code;}

    void setId(unsigned int const i) {this->id = i;}
    void setCode(std::string const c) {this->code = c;}

    bool operator== (const Node &other) {
        return this->id = other.id;
    }
};

#endif //DA_PROJ1_NODE_H
