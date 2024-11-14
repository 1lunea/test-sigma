#ifndef NUMBER_SYSTEM_H
#define NUMBER_SYSTEM_H

#include <string>

class NumberSystem {
public:
    // Decimal to other bases
    std::string decimalToHex(long long decimal);
    std::string decimalToBinary(long long decimal);
    std::string decimalToOctal(long long decimal);
    
    // Other bases to decimal
    long long hexToDecimal(const std::string& hex);
    long long binaryToDecimal(const std::string& binary);
    long long octalToDecimal(const std::string& octal);
    
    // Direct conversions
    std::string hexToBinary(const std::string& hex);
    std::string binaryToHex(const std::string& binary);
};

#endif 