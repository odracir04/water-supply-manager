#include "Interface.h"
#include "Reservoir.h"
#include <iostream>

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
    } while (false); // manager.validateReservoir

    return option;
}

string Interface::readStation() {
    string option;
    do {
        cout <<"\n\tInsert a " << BLUE << "station code" << RESET <<  " (e.g. PS_1): " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (false); // manager.validateStation

    return option;
}

pair<string, string> Interface::readPipeline() {
    string option1;
    do {
        cout <<"\n\tInsert a " << BLUE << " pipe source" << RESET <<  " (e.g. R_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option1;
        cin.ignore();
    } while (false); // manager.validateReservoir || manager.validateStation

    string option2;
    do {
        cout <<"\n\tInsert a " << BLUE << " pipe destination" << RESET <<  " (e.g. C_1 / PS_1): " << RESET;
        cin.clear();
        cin >> option1;
        cin.ignore();
    } while (false); // manager.validateCity || manager.validateStation

    return {option1, option2};
}

void Interface::init() {
    // this.manager = Manager();
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
        parser = Parser(option - 1);
        parser.readData();
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

    switch(option) {
        case 0:
            mainMenu();
            break;
        case 1:
            clear();
            // manager.getWaterSupplyCity
            // printWaterSupplyCity
            break;
        case 2:
            clear();
            // manager.getWaterSupplyAllCities
            // // printWaterSupplyAllCities
            break;
        case 3:
            clear();
            // manager.getRequirementsSatisfaction
            // printRequirementsSatisfaction
            break;
        case 4:
            clear();
            // manager.balanceNetworkFlow
            // printNetworkFlow
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
            // manager.checkReservoirFailure(readReservoir())
            clear();
            printNetworkFlow();
            break;
        case 2:
            // manager.checkStationFailure(readStation())
            clear();
            // printNetworkFlow
            break;
        case 3:
            // manager.checkPipeFailure(readPipeline())
            clear();
            // printNetworkFlow
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

void Interface::printNetworkFlow() {

    for (const Vertex<Node*>* vertex : parser.waterNetwork.getVertexSet()) {
        Node* node = vertex->getInfo();

        std::cout << node->getId() << " -- " << node->getCode() << std::endl;
    }
}