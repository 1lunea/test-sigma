#include "NumberFormat.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace {
    // Constants
    constexpr double DEFAULT_TOLERANCE = 1e-10;
    constexpr long long MAX_DENOMINATOR = 1000000;
}

Fraction NumberFormat::decimalToFraction(double decimal, double tolerance) {
    if (std::isnan(decimal) || std::isinf(decimal)) {
        throw std::runtime_error("Cannot convert NaN or infinity to fraction");
    }

    // Handle negative numbers
    bool isNegative = decimal < 0;
    decimal = std::abs(decimal);

    // Handle whole numbers
    if (isApproximatelyInteger(decimal, tolerance)) {
        return Fraction(static_cast<long long>(std::round(decimal)) * (isNegative ? -1 : 1), 1);
    }

    // Convert decimal to fraction using continued fraction algorithm
    long long numerator = findBestFraction(decimal, MAX_DENOMINATOR);
    long long denominator = findBestFraction(1.0 / decimal, MAX_DENOMINATOR);

    if (numerator == 0 || denominator == 0) {
        throw std::runtime_error("Could not convert to fraction");
    }

    return Fraction(numerator * (isNegative ? -1 : 1), denominator);
}

std::string NumberFormat::formatNumber(double value, bool asFraction) {
    if (std::isnan(value)) return "NaN";
    if (std::isinf(value)) return value > 0 ? "∞" : "-∞";
    
    if (asFraction) {
        try {
            Fraction frac = decimalToFraction(value);
            return frac.toString();
        } catch (const std::exception&) {
            // If conversion fails, fall back to decimal
            asFraction = false;
        }
    }
    
    // Format as decimal
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6);
    oss << value;
    std::string str = oss.str();
    
    // Remove trailing zeros after decimal point
    size_t decimalPos = str.find('.');
    if (decimalPos != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1);
        if (str.back() == '.') {
            str.pop_back();
        }
    }
    return str;
}

bool NumberFormat::isApproximatelyInteger(double value, double tolerance) {
    if (tolerance <= 0) {
        tolerance = DEFAULT_TOLERANCE;
    }
    return std::abs(value - std::round(value)) < tolerance;
}

long long NumberFormat::findBestFraction(double value, long long maxDenominator) {
    if (maxDenominator <= 0) {
        maxDenominator = MAX_DENOMINATOR;
    }

    double intPart;
    double fracPart = std::modf(value, &intPart);
    
    if (fracPart < DEFAULT_TOLERANCE) {
        return static_cast<long long>(intPart);
    }
    
    // Use continued fraction expansion
    long long n0 = 0, n1 = 1;
    long long d0 = 1, d1 = 0;
    double x = value;
    
    while (true) {
        if (std::abs(x) > static_cast<double>(LLONG_MAX)) {
            throw std::overflow_error("Value too large for fraction conversion");
        }
        
        long long a = static_cast<long long>(x);
        long long n2 = a * n1 + n0;
        long long d2 = a * d1 + d0;
        
        // Check for overflow
        if (n2 < 0 || d2 < 0 || d2 > maxDenominator) {
            break;
        }
        
        n0 = n1; n1 = n2;
        d0 = d1; d1 = d2;
        
        double newX = 1.0 / (x - a);
        if (std::isinf(newX) || std::abs(newX) < DEFAULT_TOLERANCE) {
            break;
        }
        x = newX;
    }
    
    return n1;
} 