
#ifndef DA_PROJ1_PIPE_H
#define DA_PROJ1_PIPE_H

#include <string>


class Pipe {
    private:
        std::string servicePointA;
        std::string servicePointB;
        int capacity;
        double flow;
        bool direction;

    public:

        /**
         * @brief Pipe constructor.
         * @param s Source vertex.
         * @param d Destination vertex.
         * @param w Weight of the vertex.
         */
        Pipe(const std::string &s, const std::string &d, double &w, bool direction);

        /**
         * Getter for the flow of the pipe.
         * @return Flow of the pipe.
         */
        double getFlow() const;

        /**
         * Setter for the flow of the pipe.
         * @param f Flow of the city.
         */
        void setFlow(double f);

        /**
         * Getter for the destination vertex.
         * @return destination vertex code.
         */
        std::string getDest() const;

        /**
         * Getter for the source vertex.
         * @return source vertex code.
         */
        std::string getOrig() const;

        /**
         * Getter for the weight of the pipe.
         * @return weight of the pipe.
         */
        double getWeight() const;

        /**
         * Setter for the weight of the pipe.
         * @param weight weight to be set.
         */
        void setWeight(double weight);

        /**
         * Getter for the direction of the pipe.
         * @return 0 for bidirectional and  1 for unidirectional.
         */
        bool getDirection();
};


#endif //DA_PROJ1_PIPE_H
