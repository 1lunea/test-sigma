#include "ScientificOperations.h"
#include <cmath>
#include <stdexcept>

double ScientificOperations::sin(double angle) {
    return std::sin(toRadians(angle));
}

double ScientificOperations::cos(double angle) {
    return std::cos(toRadians(angle));
}

double ScientificOperations::tan(double angle) {
    return std::tan(toRadians(angle));
}

double ScientificOperations::log(double number) {
    if (number <= 0) {
        throw std::runtime_error("Cannot calculate logarithm of non-positive number!");
    }
    return std::log10(number);
}

double ScientificOperations::ln(double number) {
    if (number <= 0) {
        throw std::runtime_error("Cannot calculate natural logarithm of non-positive number!");
    }
    return std::log(number);
}

double ScientificOperations::factorial(int number) {
    if (number < 0) {
        throw std::runtime_error("Cannot calculate factorial of negative number!");
    }
    double result = 1;
    for (int i = 2; i <= number; ++i) {
        result *= i;
    }
    return result;
}

double ScientificOperations::toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double ScientificOperations::toDegrees(double radians) {
    return radians * 180.0 / M_PI;
} 