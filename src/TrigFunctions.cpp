#include "TrigFunctions.h"
#include <cmath>
#include <stdexcept>

namespace {
    constexpr double PI = 3.14159265358979323846;
    
    double toRadians(double angle, bool isDegrees) {
        return isDegrees ? angle * PI / 180.0 : angle;
    }
}

double TrigFunctions::sin(double angle, bool isDegrees) {
    return std::sin(toRadians(angle, isDegrees));
}

double TrigFunctions::cos(double angle, bool isDegrees) {
    return std::cos(toRadians(angle, isDegrees));
}

double TrigFunctions::tan(double angle, bool isDegrees) {
    return std::tan(toRadians(angle, isDegrees));
}

double TrigFunctions::csc(double angle, bool isDegrees) {
    double sinVal = sin(angle, isDegrees);
    if (sinVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / sinVal;
}

double TrigFunctions::sec(double angle, bool isDegrees) {
    double cosVal = cos(angle, isDegrees);
    if (cosVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / cosVal;
}

double TrigFunctions::cot(double angle, bool isDegrees) {
    double tanVal = tan(angle, isDegrees);
    if (tanVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / tanVal;
}

// Inverse trig functions (always return radians)
double TrigFunctions::arcsin(double value) {
    if (value < -1 || value > 1) 
        throw std::runtime_error("Domain error in arcsin");
    return std::asin(value);
}

double TrigFunctions::arccos(double value) {
    if (value < -1 || value > 1) 
        throw std::runtime_error("Domain error in arccos");
    return std::acos(value);
}

double TrigFunctions::arctan(double value) {
    return std::atan(value);
}

// Hyperbolic functions
double TrigFunctions::sinh(double x) {
    return std::sinh(x);
}

double TrigFunctions::cosh(double x) {
    return std::cosh(x);
}

double TrigFunctions::tanh(double x) {
    return std::tanh(x);
}

double TrigFunctions::csch(double x) {
    double sinhVal = sinh(x);
    if (sinhVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / sinhVal;
}

double TrigFunctions::sech(double x) {
    double coshVal = cosh(x);
    if (coshVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / coshVal;
}

double TrigFunctions::coth(double x) {
    double tanhVal = tanh(x);
    if (tanhVal == 0) throw std::runtime_error("Undefined (division by zero)");
    return 1.0 / tanhVal;
}

// Inverse hyperbolic functions
double TrigFunctions::arsinh(double x) {
    return std::asinh(x);
}

double TrigFunctions::arcosh(double x) {
    if (x < 1) throw std::runtime_error("Domain error in arcosh");
    return std::acosh(x);
}

double TrigFunctions::artanh(double x) {
    if (x <= -1 || x >= 1) throw std::runtime_error("Domain error in artanh");
    return std::atanh(x);
} 