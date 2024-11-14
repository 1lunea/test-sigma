#include "Display.h"
#include <iostream>

void Display::clear() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Display::showResult(double result) const {
    std::cout << "Result: " << result << std::endl;
}

void Display::showError(const std::string& message) const {
    std::cout << "Error: " << message << std::endl;
}

void Display::showMessage(const std::string& message) const {
    std::cout << message << std::endl;
} 