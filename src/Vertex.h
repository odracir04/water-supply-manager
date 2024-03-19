#ifndef DA_PROJ1_VERTEX_H
#define DA_PROJ1_VERTEX_H
#include <vector>
#include "Pipe.h"

class Vertex {
    private:
        std::string code;                // contents
        std::vector<Pipe> adj;  // list of outgoing Pipes
        bool visited;          // auxiliary field
        bool processing;       // auxiliary field
        int indegree;          // auxiliary field
        int num;               // auxiliary field
        int low;               // auxiliary field

        void addPipe(const std::string &dest, const int &w);
        bool removePipeTo(std::string *d);

    public:
        Vertex(std::string code);
        virtual std::string getCode() const;
        void setCode(std::string in);
        bool isVisited() const;
        void setVisited(bool v);
        bool isProcessing() const;
        void setProcessing(bool p);
        int getIndegree() const;
        void setIndegree(int indegree);
        void setLow(int low);
        void setNum(int num);
        int getNum() const;
        int getLow() const;

        const std::vector<Pipe> &getAdj() const;
        void setAdj(const std::vector<Pipe> &adj);
        friend class Graph;
};

#endif //DA_PROJ1_VERTEX_H
