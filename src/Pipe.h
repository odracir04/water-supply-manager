
#ifndef DA_PROJ1_PIPE_H
#define DA_PROJ1_PIPE_H

#include <string>


class Pipe {
    private:
        std::string servicePointA;
        std::string servicePointB;
        int capacity;
        double flow;
        Pipe* reverse;

    public:

        /**
         * @brief Pipe constructor.
         * @param s Source vertex.
         * @param d Destination vertex.
         * @param w Weight of the vertex.
         */
        Pipe(const std::string &s, const std::string &d, double &w);

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
        Pipe* getReverse() const;


        /**
         * Getter for the weight of the pipe.
         * @return weight of the pipe.
         */
        double getWeight() const;

        void setDest(std::string *dest);

        /**
         * Setter for the weight of the pipe.
         * @param weight weight to be set.
         */
        void setWeight(double weight);
        void setReverse(Pipe* pipe);


};


#endif //DA_PROJ1_PIPE_H
