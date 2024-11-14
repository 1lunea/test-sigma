#ifndef SCIENTIFIC_SYMBOLS_H
#define SCIENTIFIC_SYMBOLS_H

#include <string>
#include <map>

class ScientificSymbols {
public:
    static const std::map<std::string, std::string> SYMBOLS;
    static const std::map<std::string, double> CONSTANTS;
    
    // Get symbol or constant value
    static std::string getSymbol(const std::string& name);
    static double getConstant(const std::string& name);
    
    // Check if string is a symbol or constant
    static bool isSymbol(const std::string& name);
    static bool isConstant(const std::string& name);
    
    // Format number with scientific notation
    static std::string formatScientific(double value, int precision = 6);
};

#endif 