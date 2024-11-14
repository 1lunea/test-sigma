#include "UnitConverter.h"
#include <stdexcept>

const std::map<std::string, double> UnitConverter::lengthFactors = {
    {"m", 1.0},
    {"km", 1000.0},
    {"cm", 0.01},
    {"mm", 0.001},
    {"in", 0.0254},
    {"ft", 0.3048},
    {"yd", 0.9144},
    {"mi", 1609.344}
};

const std::map<std::string, double> UnitConverter::massFactors = {
    {"kg", 1.0},
    {"g", 0.001},
    {"mg", 0.000001},
    {"lb", 0.45359237},
    {"oz", 0.028349523125}
};

const std::map<std::string, double> UnitConverter::timeFactors = {
    {"s", 1.0},
    {"min", 60.0},
    {"hr", 3600.0},
    {"day", 86400.0}
};

const std::map<std::string, double> UnitConverter::angleFactors = {
    {"rad", 1.0},
    {"deg", 0.017453292519943295}, // π/180
    {"grad", 0.015707963267948967} // π/200
};

double UnitConverter::convert(UnitType type, const std::string& fromUnit, 
                            const std::string& toUnit, double value) {
    if (type == UnitType::TEMPERATURE) {
        return convertTemperature(fromUnit, toUnit, value);
    }

    const std::map<std::string, double>* factors;
    switch (type) {
        case UnitType::LENGTH:
            factors = &lengthFactors;
            break;
        case UnitType::MASS:
            factors = &massFactors;
            break;
        case UnitType::TIME:
            factors = &timeFactors;
            break;
        case UnitType::ANGLE:
            factors = &angleFactors;
            break;
        default:
            throw std::runtime_error("Invalid unit type");
    }

    if (factors->find(fromUnit) == factors->end() || 
        factors->find(toUnit) == factors->end()) {
        throw std::runtime_error("Invalid unit");
    }

    return value * factors->at(fromUnit) / factors->at(toUnit);
}

double UnitConverter::convertTemperature(const std::string& fromUnit, 
                                       const std::string& toUnit, double value) {
    // Convert to Kelvin first
    double kelvin;
    if (fromUnit == "K") kelvin = value;
    else if (fromUnit == "C") kelvin = value + 273.15;
    else if (fromUnit == "F") kelvin = (value + 459.67) * 5.0/9.0;
    else throw std::runtime_error("Invalid temperature unit");

    // Convert from Kelvin to target unit
    if (toUnit == "K") return kelvin;
    else if (toUnit == "C") return kelvin - 273.15;
    else if (toUnit == "F") return kelvin * 9.0/5.0 - 459.67;
    else throw std::runtime_error("Invalid temperature unit");
} 