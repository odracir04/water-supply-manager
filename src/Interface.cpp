#include "Interface.h"
#include "Reservoir.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Interface::clear() {
    system("clear");
}

void Interface::header() {
    clear();
    std::cout << BOLD << " _______________________________________________________________________________________________\n"
              << "/-----/-----/-----/-----/-----/-----/-----/-----\\-----\\-----\\-----\\-----\\-----\\-----\\-----\\-----\\\n"
              << "" << RESET << "|------------------------------- " << BOLD << BLUE << "Water Supply Manager (Group 5)" << RESET <<" --------------------------------|" << BOLD << "\n\n" << RESET;
}

void Interface::footer() {

    std::cout << BOLD << "|------------------------------  " << BOLD << BLUE << "Water Supply Manager (Group 5)" << RESET << " --------------------------------|\n";
}

void Interface::inputWait() {
    cin.clear();
    cout << "\n\n\t\t\t\t  " << FAINT << "< Press " << RESET << BOLD << "ENTER" << RESET << FAINT << " to Continue >" << RESET;
    cin.ignore();
}

int Interface::readOption(unsigned int options) {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tOption: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!(option.size() == 1 && "0" <= option && option <= to_string(options)));

    return stoi(option);
}

string Interface::readReservoir() {
    string option;
    do {
        clear();
        header();
        cout <<"\n\tInsert a " << BLUE << "reservoir code" << RESET <<  " (e.g. R_1): " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!manager.validateReservoir(option));

    return option;
}

string Interface::readStation() {
    string option;
    do {
        clear();
        header();
        cout <<"\n\tInsert a " << BLUE << "station code" << RESET <<  " (e.g. PS_1): " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!manager.validateStation(option));

    return option;
}

string Interface::readCity() {
    string option;
    do {
        clear();
        header();
        cout <<"\n\tInsert a " << BLUE << "city code" << RESET <<  " (e.g. C_1): " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!manager.validateCity(option));

    return option;
}

pair<string, string> Interface::readPipeline() {
    string option1, option2;
    do {
        clear();
        header();
        cout <<"\n\tInsert a " << BLUE << "pipe source" << RESET <<  " (e.g. R_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option1;
        cin.ignore();
        cout <<"\n\tInsert a " << BLUE << "pipe destination" << RESET <<  " (e.g. C_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option2;
        cin.ignore();
    } while (!manager.validatePipe(option1, option2));

    return {option1, option2};
}

void Interface::init() {
    startMenu();
}

void Interface::startMenu() {
    header();

    cout << FAINT << YELLOW << "\tWhich dataset would you like to load?\n\n" << RESET;

    cout << BOLD << BLUE << "\t[1]" << RESET << " - Small Dataset" << "\n"
    << BOLD << BLUE << "\t[2]" << RESET << " - Large Dataset" << "\n"
    << BOLD << RED << "\t[0]" << RESET << " - Exit\n\n";

    footer();

    int option = readOption(2);

    if (option == 0)
        exitMenu();
    else {
        manager.extractFiles(option - 1);
    }

    mainMenu();
}

void Interface::exitMenu() {
    header();

    cout << BOLD << "\t\t\t  Thank you for using our Water Supply Manager!\n\n" << RESET;

    footer();
    exit(0);
}

void Interface::servicesMenu() {
    header();

    cout << FAINT << YELLOW << "\tWhat are you looking for today?\n\n" << RESET;

    cout << BOLD << BLUE << "\t[1]" << RESET << " - Water Supply (City)\n"
         << BOLD << BLUE << "\t[2]" << RESET << " - Water Supply (All Cities)\n"
         << BOLD << BLUE << "\t[3]" << RESET << " - Network Flow Balance\n"
         << BOLD << RED << "\t[0]" << RESET << " - Back\n\n";

    footer();

    int option = readOption(4);
    string city;

    switch(option) {
        case 0:
            mainMenu();
            break;
        case 1:
            clear();
            city = readCity();
            manager.maxFlowCities(city);
            printWaterSupplyCity(city);
            break;
        case 2:
            //clear();
            manager.maxFlowAllCities();
            printWaterSupplyAllCities();
            break;
        case 3:
            clear();
            // printNetworkMetrics();
            manager.balanceWaterFlow();
            // printNetworkMetrics();
            break;
    }

    inputWait();
    servicesMenu();
}

void Interface::pipeFailureMenu() {
    clear();
    header();

    cout << FAINT << YELLOW << "\tWhat are you looking for today?\n\n" << RESET;

    cout << BLUE << BOLD << "\t[1]" << RESET << " - Display Cities affected by Pipe\n"
         << BLUE << BOLD << "\t[2]" << RESET << " - Display Pipes vital to City\n"
         << RED << BOLD << "\t[0]" << RESET << " - Back\n\n";

    footer();

    int option = readOption(2);

    switch(option) {
        case 0:
            reliabilityMenu();
            break;
        case 1:
            manager.checkPipeFailure(readPipeline());
            break;
        case 2:
            manager.checkVitalPipes(readCity());

    }
}

void Interface::reliabilityMenu() {
    header();

    cout << FAINT << YELLOW << "\tWhat are you looking for today?\n\n" << RESET;

    cout << BLUE << BOLD << "\t[1]" << RESET << " - Resilience to Water Reservoir Failure\n"
    << BLUE << BOLD << "\t[2]" << RESET << " - Resilience to Pumping Station Failure\n"
    << BLUE << BOLD << "\t[3]" << RESET << " - Resilience to Pipeline Failure\n"
    << RED << BOLD << "\t[0]" << RESET << " - Back\n\n";

    footer();

    int option = readOption(3);

    switch (option) {
        case 0:
            mainMenu();
            break;
        case 1:
            printCitiesInDeficit(manager.checkReservoirFailure(readReservoir()));
            break;
        case 2:
            printCitiesInDeficit(manager.checkStationFailure(readStation()));
            break;
        case 3:
            pipeFailureMenu();
            break;
    }

    inputWait();
    reliabilityMenu();

}

void Interface::mainMenu() {
    header();

    cout << FAINT << YELLOW << "\tWhat are you looking for today?\n\n" << RESET;

    cout << BLUE << BOLD << "\t[1]" << RESET << " - Basic Service Metrics\n"
    << BLUE << BOLD << "\t[2]" << RESET << " - Reliability and Failure Tolerance\n"
    << RED << BOLD << "\t[0]" << RESET << " - Back\n\n";

    footer();

    int option = readOption(2);

    switch(option) {
        case 0:
            manager.resetGraph();
            startMenu();
            break;
        case 1:
            servicesMenu();
            break;
        case 2:
            reliabilityMenu();
            break;
    }

}

void Interface::printWaterSupplyCity(string option) {
    City* city = manager.getCity(option);
    std::stringstream ss;

    if (city != nullptr) {
        printSupplyHeader(manager);
      
        cout << left << "| " << setw(15) << city->getCode()
             << "| " << setw(15) << city->getDemand()
             << "| " << setw(15) << city->getIncome()
             << "| " << ((city->getDemand() - city->getIncome() <= 0) ? GREEN : RED) << setw(15)
             << ((city->getDemand() - city->getIncome() <= 0) ? "SUPPLIED" : "NOT SUPPLIED") << RESET
             << "| " << setw(30) << city->getName() << endl;
      
        ss << std::left << "| " << std::setw(15) << city->getPopulation()
           << "| " << std::setw(15) << city->getDemand()
           << "| " << std::setw(15) << city->getIncome()
           << "| " << setw(15)<<(((city->getDemand() - city->getIncome()) <= 0) ? "SUPPLIED" : "NOT SUPPLIED")
           << "| " << std::setw(30) << city->getName() << std::endl;

        inputWait();
    }
    manager.getLogger()->log(ss.str());
    servicesMenu();
}

void Interface::printWaterSupplyAllCities() {
    printSupplyHeader(manager);
    std::vector<City*> cities = manager.getCities();

    std::stringstream ss;

    double total_flow = 0;
    for (const City* city : cities) {
        total_flow += city->getIncome();
        cout << left << "| " << setw(15) << city->getCode()
             << "| " << setw(15) << city->getDemand()
             << "| " << setw(15) << city->getIncome()
             << "| " << ((city->getDemand() - city->getIncome() <= 0) ? GREEN : RED) << setw(15)
             << ((city->getDemand() - city->getIncome() <= 0) ? "SUPPLIED" : "NOT SUPPLIED") << RESET
             << "| " << setw(30) << city->getName() << endl;

        ss << std::left << "| " << std::setw(15) << city->getPopulation()
           << "| " << std::setw(15) << city->getDemand()
           << "| " << std::setw(15) << city->getIncome()
           << "| " <<setw(15) <<(((city->getDemand() - city->getIncome())<= 0) ? "SUPPLIED" : "NOT SUPPLIED")
           << "| " << std::setw(30) << city->getName() << std::endl;
    }

    cout << YELLOW << BOLD << "\n\nTotal Flow: " << RESET << total_flow << endl;
    inputWait();
    manager.getLogger()->log(ss.str());
    servicesMenu();
}


void Interface::printCitiesInDeficit(std::vector<City*> cities) {
    clear();
    cout << left << BOLD << "| " << BLUE << setw(15) << "Code" << RESET
    << BOLD << "| " << BLUE << setw(15) << "Deficit" << RESET
    << BOLD << "| " << BLUE << setw(30) << "Name" << RESET << endl;

    for (const City* city : cities) {
        if (city->getDemand() > city->getIncome()) {
            cout << left << "| " << setw(15) << city->getCode()
                 << "| " << setw(15) << city->getDemand() - city->getIncome()
                 << "| " << setw(30) << city->getName() << RESET << endl;
        }
    }
    inputWait();
    reliabilityMenu();
}

void Interface::printSupplyHeader(Manager &man) {
    
    std::stringstream ss;

    cout << left << BOLD << "| " << BLUE << setw(15) << "Code" << RESET
         << BOLD << "| " << BLUE << setw(15) << "Demand" << RESET
         << BOLD << "| " << BLUE << setw(15) << "Supply" << RESET
         << BOLD << "| " << BLUE << setw(15) << "Status" << RESET
         << BOLD << "| " << BLUE << setw(30) << "Name" << RESET << endl;

    ss << left <<   "\n\n| "<< setw(15) << "Population"
                 <<   "| " <<  setw(15) << "Demand"
                 <<   "| " <<  setw(15) << "Supply"
                 <<   "| " <<  setw(15) << "Status"
                 <<   "| " <<  setw(30) << "Name";
    man.getLogger()->log(ss.str());
}

