#ifndef TRIG_FUNCTIONS_H
#define TRIG_FUNCTIONS_H

class TrigFunctions {
public:
    // Regular trigonometric functions
    double sin(double angle, bool isDegrees = true);
    double cos(double angle, bool isDegrees = true);
    double tan(double angle, bool isDegrees = true);
    double csc(double angle, bool isDegrees = true);
    double sec(double angle, bool isDegrees = true);
    double cot(double angle, bool isDegrees = true);
    
    // Inverse trigonometric functions
    double arcsin(double value);
    double arccos(double value);
    double arctan(double value);
    
    // Hyperbolic functions
    double sinh(double x);
    double cosh(double x);
    double tanh(double x);
    double csch(double x);
    double sech(double x);
    double coth(double x);
    
    // Inverse hyperbolic functions
    double arsinh(double x);
    double arcosh(double x);
    double artanh(double x);
};

#endif 