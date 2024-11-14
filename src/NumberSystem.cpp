#include "NumberSystem.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string NumberSystem::decimalToHex(long long decimal) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << decimal;
    return ss.str();
}

std::string NumberSystem::decimalToBinary(long long decimal) {
    if (decimal == 0) return "0";
    std::string binary;
    bool isNegative = decimal < 0;
    decimal = std::abs(decimal);
    
    while (decimal > 0) {
        binary = (decimal % 2 ? "1" : "0") + binary;
        decimal /= 2;
    }
    return isNegative ? "-" + binary : binary;
}

std::string NumberSystem::decimalToOctal(long long decimal) {
    std::stringstream ss;
    ss << std::oct << decimal;
    return ss.str();
}

long long NumberSystem::hexToDecimal(const std::string& hex) {
    std::stringstream ss;
    ss << std::hex << hex;
    long long decimal;
    ss >> decimal;
    if (ss.fail()) {
        throw std::runtime_error("Invalid hexadecimal number");
    }
    return decimal;
}

long long NumberSystem::binaryToDecimal(const std::string& binary) {
    long long decimal = 0;
    bool isNegative = binary[0] == '-';
    size_t start = isNegative ? 1 : 0;
    
    for (size_t i = start; i < binary.length(); ++i) {
        if (binary[i] != '0' && binary[i] != '1') {
            throw std::runtime_error("Invalid binary number");
        }
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return isNegative ? -decimal : decimal;
}

long long NumberSystem::octalToDecimal(const std::string& octal) {
    std::stringstream ss;
    ss << std::oct << octal;
    long long decimal;
    ss >> decimal;
    if (ss.fail()) {
        throw std::runtime_error("Invalid octal number");
    }
    return decimal;
}

std::string NumberSystem::hexToBinary(const std::string& hex) {
    return decimalToBinary(hexToDecimal(hex));
}

std::string NumberSystem::binaryToHex(const std::string& binary) {
    return decimalToHex(binaryToDecimal(binary));
} 