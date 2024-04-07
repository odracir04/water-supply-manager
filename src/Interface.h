#ifndef DA_PROJ1_INTERFACE_H
#define DA_PROJ1_INTERFACE_H

// Text Formatting
#include <string>
#include <unordered_map>
#include "Parser.h"
#include "Manager.h"
#include "Logger.h"

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define FAINT       "\033[2m"

// Text Colors (Foreground)
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"

class Interface {
private:
    Manager manager;
    /**
     * @brief Prints the header for the interactive menu.
     */
    static void header();

    /**
     * @brief Prints the footer for the interactive menu.
     */
    static void footer();

    /**
     * @brief Clears the terminal.
     */
    static void clear();

    /**
     * Prints the header for the supply menu and outputs to a file.
     * @param man Manager instance for accessing the Logger class.
     */
    static void printSupplyHeader(Manager &man);

    /**
     * @brief Waits for the input in order to leave the menu.
     */
    static void inputWait();

public:
    /**
     * @brief Calls the initial menu function..
     */
    void init();


    /**
     * Prints initial menu and calls the extractFiles function to parse the files.
     */
    void startMenu();

    /**
     * @brief Prints the main menu.
     */
    void mainMenu();

    /**
     * Prints the exit menu and leaves the application.
     */
    static void exitMenu();

    /**
     * Prints the services menu.
     * Allows the access to some algorithms.
     * Complexity: Depends on user choice.
     */
    void servicesMenu();

    /**
     * Prints the reliability menu.
     * Allows the access to some failure algorithms.
     * Complexity: Depends on user choice.
     */
    void reliabilityMenu();

    /**
     * Prints the pipe failure menu.
     * Allows the user to chose which pipe failure algorithm to display.
     * Complexity: Depends on user choice.
     */
    void pipeFailureMenu();

    /**
     * Prints a confirmation message.
     * @return True if the user wishes to proceed.
     * Complexity: Depends on user choice.
     */
    bool confirmationMenu();

    /**
     * Prints the parameters of single City according to user input, it also outputs to a file.
     * @param option The city code chosen by user input.
     * Complexity: O(v) where v is the number of vertexes.
     */
    void printWaterSupplyCity(std::string option);

    /**
     * Prints all the cities in deficit.
     * @param cities The cities to be printed.
     */
    void printAffectedCities(std::unordered_map<City*, unsigned int>  cities);
  
    /**
     * Prints all the cities and their parameters, and outputs to a file.
     * Complexity: O(v) where v is the number of vertexes.
     */
    void printWaterSupplyAllCities();
  
    /**
     * Prints all pipes vital to a cities supply.
     * Complexity: O(v), where v is the nnumber of vertexes.
     * @param city The city to be analyzed.
     */
    void printVitalPipes(std::pair<City*, std::vector<Pipe*>> city);

    /**
     * Asks the user to chose an option in the different menus, based on an integer user input.
     * @param options Number of possible options in the specific menu
     * @return The option chosen.
     */
    static int readOption(unsigned int options);

    /**
     * Asks the user to input a valid Reservoir code.
     * Complexity: O(v) where v is the number of vertexes.
     * @return Code of the reservoir.
     */
    std::string readReservoir();

    /**
     * Asks the user to input a valid Station code.
     * Complexity: O(v) where v is the number of vertexes.
     * @return Code of the Station
     */
    std::string readStation();

    /**
     * Asks the user to input a valid Pipe connection.
     * Complexity: O(v) where v is the number of vertexes.
     * @return A pair containing the code of the both connectors.
     */
    std::pair<std::string, std::string> readPipeline();

    /**
     * Asks the user to input a valid City.
     * Complexity: O(v) where v is the number of vertexes.
     * @return Code of the City.
     */
    std::string readCity();

    /**
     * Prints a series of network metrics before and after running the balance flow algorithm.
     * Complexity: O(1)
     */
    void printNetworkMetrics();
};


#endif //DA_PROJ1_INTERFACE_H
