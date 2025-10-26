#include "Array.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <system_error>

#include "Figure.hpp"
#include "Hexagon.hpp"
#include "Octagon.hpp"
#include "Pentagon.hpp"

int main() {
    try {
        std::cout << "Welcome to Lab3OOPFigureWorkerProgramm_V1!" << std::endl;
        ArrayF spis;
        int choice = 0;
        std::cout << "Select an action: " << std::endl;
        std::cout << "Choose an option:\n0. Exit\n1. Add pentagon\n2. Add hexagon\n3. Add oktagon\n4. Print all figures\n5. "
                     "Print total arrea\n6. Delete figure\n7. Menu"
                  << std::endl;
        std::cin >> choice;
        while (choice != 0) {
            switch (choice) {
            case 1: {
                Pentagon *pent = new Pentagon();
                std::cout << "Please, enter 5 vertices for the pentagon:" << std::endl;
                std::cin >> *pent;
                spis.PushItem(pent);
                std::cout << "Added a pentagon" << std::endl;
                break;
            }
            case 2: {
                Hexagon *hex = new Hexagon();
                std::cout << "Please, enter 6 vertices for the hexagon:" << std::endl;
                std::cin >> *hex;
                spis.PushItem(hex);
                std::cout << "Added a hexagone" << std::endl;
                break;
            }
            case 3: {
                Octagon *oct = new Octagon();
                std::cout << "Please, enter 8 vertices for the octagon:" << std::endl;
                std::cin >> *oct;
                spis.PushItem(oct);
                std::cout << "Added a octagone" << std::endl;
                break;
            }
            case 4: {
                std::cout << "All figures:" << std::endl;
                for (size_t i = 0; i < spis.GetSize(); ++i) {
                    std::cout << "Figure " << i + 1 << "\n";
                    spis.GetItem(i)->print(std::cout);
                    std::cout << "Geometric center - " << (spis.GetItem(i))->geomCenter();
                    std::cout << "; Area - " << static_cast<double>(*spis.GetItem(i));
                    std::cout << std::endl;
                }
                break;
            }
            case 5: {
                double total_area = 0.0;
                for (size_t i = 0; i < spis.GetSize(); ++i) {
                    total_area += static_cast<double>(*spis.GetItem(i));
                }
                std::cout << "Total area of all figures: " << total_area << std::endl;
                break;
            }
            case 6: {
                std::cout << "Enter index of the figure to delete: ";
                size_t ind;
                std::cin >> ind;
                if (ind <= spis.GetSize()) {
                    spis.DeleteItem(ind - 1);
                    std::cout << "Figure at index " << ind << " deleted." << std::endl;
                } else {
                    std::cout << "Invalid index." << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "Choose an option:\n0. Exit\n1. Add pentagon\n2. Add hexagon\n3. Add oktagon\n4. Print all "
                             "figures\n5. Print total arrea\n6. Delete figure\n7. Menu"
                          << std::endl;
                break;
            }
            }
            std::cout << "\nSelect an action: " << std::endl;
            std::cin >> choice;
        }
        std::cout << "Bye!\n" << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}