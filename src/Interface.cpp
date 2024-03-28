#include "Interface.h"
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
        cout <<"\n\tInsert a " << BLUE << " pipe source" << RESET <<  " (e.g. R_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option1;
        cin.ignore();
        cout <<"\n\tInsert a " << BLUE << " pipe destination" << RESET <<  " (e.g. C_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option1;
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
         << BOLD << BLUE << "\t[3]" << RESET << " - Requirements Satisfaction\n"
         << BOLD << BLUE << "\t[4]" << RESET << " - Network Flow Balance\n"
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
            clear();
            manager.maxFlowAll();
            printWaterSupplyAllCities();
            break;
        case 3:
            clear();
            manager.checkNetworkRequirements();
            break;
        case 4:
            clear();
            manager.balanceWaterFlow();
            printWaterSupplyAllCities();
            break;
    }

    inputWait();
    servicesMenu();
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
            manager.checkReservoirFailure(readReservoir());
            clear();
            printWaterSupplyAllCities();
            break;
        case 2:
            manager.checkStationFailure(readStation());
            clear();
            printWaterSupplyAllCities();
            break;
        case 3:
            manager.checkPipeFailure(readPipeline());
            clear();
            printWaterSupplyAllCities();
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
        double deficit = (city->getDemand() - city->getIncome());
        cout << left << "| " << setw(15) << city->getPopulation()
             << "| " << setw(15) << city->getDemand()
             << "| " << setw(15) << city->getIncome()
             << "| " << ((deficit < 0) ? GREEN : RED) << setw(15)
             << ((deficit <= 0) ? "SUPPLIED" : "NOT SUPPLIED") << RESET
             << "| " << setw(30) << city->getName() << endl;


        ss << std::left << "| " << std::setw(15) << city->getPopulation()
           << "| " << std::setw(15) << city->getDemand()
           << "| " << std::setw(15) << city->getIncome() << setw(15)
           << "| " << setw(15)<<((deficit <= 0) ? "SUPPLIED" : "NOT SUPPLIED")
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

    for (const City* city : cities) {
        double deficit = (city->getDemand() - city->getIncome());
        cout << left << "| " << setw(15) << city->getPopulation()
             << "| " << setw(15) << city->getDemand()
             << "| " << setw(15) << city->getIncome()
             << "| " << ((deficit < 0) ? GREEN : RED) << setw(15)
             << ((deficit < 0) ? "SUPPLIED" : "NOT SUPPLIED") << RESET
             << "| " << setw(30) << city->getName() << endl;

        ss << std::left << "| " << std::setw(15) << city->getPopulation()
           << "| " << std::setw(15) << city->getDemand()
           << "| " << std::setw(15) << city->getIncome()
           << "| " <<setw(15) <<((deficit <= 0) ? "SUPPLIED" : "NOT SUPPLIED")
           << "| " << std::setw(30) << city->getName() << std::endl;
    }
    inputWait();
    manager.getLogger()->log(ss.str());
    servicesMenu();
}

void Interface::printSupplyHeader(Manager &man) {

    stringstream ss;

    cout << left << BOLD << "\n\n| " << BLUE << setw(15) << "Population" << RESET
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

