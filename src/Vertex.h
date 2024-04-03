#ifndef DA_PROJ1_VERTEX_H
#define DA_PROJ1_VERTEX_H
#include <vector>
#include "Pipe.h"

class Vertex {
    private:
        std::string code;                // contents
        std::vector<Pipe*> adj;  // list of outgoing Pipes
        bool visited;          // auxiliary field
        bool processing;       // auxiliary field
        int indegree;          // auxiliary field
        int num;               // auxiliary field
        int low;               // auxiliary field
        Pipe *path = nullptr;

        void addPipe(const std::string &dest,double &w);
        std::vector<Pipe *> incoming;
        friend class Graph;

    public:
        /**
         * @brief Vertex constructor.
         * @param code Code of the vertex.
         */
        Vertex(std::string code);

        /**
         * Getter for Vertex code.
         * @return vertex code.
         */
        virtual std::string getCode() const;
        void setCode(std::string in);

        /**
         * Checks visited attribute.
         * @return True if vertex is visited or false otherwise.
         */
        bool isVisited() const;

        /**
         * Setter for visited attribute.
         * @param v Value to be assigned to visited attribute.
         */
        void setVisited(bool v);

        bool isProcessing() const;
        void setProcessing(bool p);
        int getIndegree() const;
        void setIndegree(int indegree);
        void setLow(int low);
        void setNum(int num);
        int getNum() const;
        int getLow() const;

        /**
         * Getter for the vertex path.
         * @return Pipe corresponding to the path of the vertex.
         */
        Pipe* getPath() const;

        /**
         * Setter for the vertex path.
         * @param path Pipe to be set as path of the vertex.
         */
        void setPath(Pipe* path);

        /**
         * Getter for a vector of pipes that correspond to the pipes incoming to the vertex.
         * @return Vector containing pipes that have the source vertex equal to the caller.
         */
        std::vector<Pipe *> getIncoming() const;

        /**
         * Getter for a vector of pipes that correspond to the pipes leaving the vertex.
         * @return Vector containing pipes that have the source vertex equal to the caller.
         */
        const std::vector<Pipe*> &getAdj() const;
        void setAdj(const std::vector<Pipe> &adj);
        friend class Graph;
};

#endif //DA_PROJ1_VERTEX_H
