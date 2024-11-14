#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include "Fraction.h"
#include <cmath>

class BasicOperations {
public:
    // Constants
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double E = 2.71828182845904523536;

    // Existing operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    // New operations
    double power(double base, double exponent);
    double nthRoot(double number, double n);
    double inverse(double number);
    
    // Fraction operations
    Fraction addFractions(const Fraction& f1, const Fraction& f2);
    Fraction subtractFractions(const Fraction& f1, const Fraction& f2);
    Fraction multiplyFractions(const Fraction& f1, const Fraction& f2);
    Fraction divideFractions(const Fraction& f1, const Fraction& f2);
    
    // Constant getters
    double getPi() const { return PI; }
    double getE() const { return E; }
};

#endif 