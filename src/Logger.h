
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
     * Construtor de um Logger.
     * Recebe apenas o nome do ficheiro onde vai escrever.
     * \n Complexidade: O(1)
     * @param filename string relativa ao nome do ficheiro de log.
     */
    Logger(std::string filename);

    /**
     * Destruidor de um Logger.
     * Verifica se ifstream está aberto e fecha.
     * \n Complexidade: O(1)
     */
    ~Logger();

    /**
     * Escritor do log.
     * Verifica se iftream aberta, captura o tempo local do sistema e escreve no ficheiro uma determinada mensagem,
     * \n Complexidade: O(1)
     * @param str String que é escrita no ficheiro.
     */
    void log(std::string str);

    Logger();
};
#endif //DA_PROJ1_LOGGER_H
