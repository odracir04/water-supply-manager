
#ifndef DA_PROJ1_LOGGER_H
#define DA_PROJ1_LOGGER_H

#include <fstream>
#include <string>
#include <ctime>

class Logger
{

private:
    std::ofstream filelog;

public:

    /**
     * Logger constructor.
     * Receives the name of file where it is going to write.
     * \n Complexity: O(1)
     * @param filename string related to the name of the file..
     */
    Logger(std::string filename);

    /**
     * Logger destructor.
     * Verifies if the ifstream is open and closes it.
     * \n Complexity: O(1)
     */
    ~Logger();

    /**
     * Logger writer.
     * Verifies if ifstream is open, and writes the content to the file.
     * \n Complexity: O(1)
     * @param str String that is written to the file.
     */
    void log(std::string str);

    Logger();
};
#endif //DA_PROJ1_LOGGER_H
