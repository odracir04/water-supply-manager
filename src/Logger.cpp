#include <iostream>
#include "Logger.h"



Logger::Logger(std::string filename) {
    filelog.open(filename);
    if (!filelog.is_open()) {
        std::cerr << "Error: Failed to open log file " << filename << std::endl;
    }
}



Logger::~Logger()
{
    if (filelog.is_open())
    {
        filelog.close();
    }
}


void Logger::log(std::string str)
{
    if (filelog.is_open())
    {

        this->filelog <<  str << std::endl;
    }
}

Logger::Logger() {

}



