#include <iostream>
#include <iomanip>
#include "include/Root.hpp"

int main() {
    double tolerance;
    int choice;

    std::cout << "Enter tolerance: ";
    std::cin >> tolerance;

    std::cout << "\nChoose Method:\n";
    std::cout << "1. Bisection Method\n";
    std::cout << "2. Newton-Raphson Method\n";
    std::cout << "3. Fixed Point Iteration Method\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    double root = 0;

    switch (choice) {
        case 1: {
            Bisection obj(tolerance);
            root = obj.solve();
            std::cout << "\nApproximate Root = " << std::setprecision(10) << root << "\n";
            break;
        }
        case 2: {
            NewtonRaphson obj(tolerance);
            root = obj.solve();
            std::cout << "\nApproximate Root = " << std::setprecision(10) << root << "\n";
            break;
        }
        case 3: {
            FixedPoint obj(tolerance);
            root = obj.solve();
            std::cout << "\nApproximate Root = " << std::setprecision(10) << root << "\n";
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
    }

    return 0;
}