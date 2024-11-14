#ifndef UNIT_CONVERTER_H
#define UNIT_CONVERTER_H

#include <string>
#include <map>

class UnitConverter {
public:
    enum class UnitType {
        LENGTH,
        MASS,
        TEMPERATURE,
        TIME,
        ANGLE
    };

    double convert(UnitType type, const std::string& fromUnit, 
                  const std::string& toUnit, double value);

private:
    // Conversion maps
    static const std::map<std::string, double> lengthFactors;
    static const std::map<std::string, double> massFactors;
    static const std::map<std::string, double> timeFactors;
    static const std::map<std::string, double> angleFactors;
    
    // Temperature needs special handling
    double convertTemperature(const std::string& fromUnit, 
                            const std::string& toUnit, double value);
};

#endif 