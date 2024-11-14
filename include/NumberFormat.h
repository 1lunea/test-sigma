#ifndef NUMBER_FORMAT_H
#define NUMBER_FORMAT_H

#include "Fraction.h"
#include <string>

class NumberFormat {
public:
    // Convert decimal to fraction
    static Fraction decimalToFraction(double decimal, double tolerance = 1e-10);
    
    // Format number as decimal or fraction string
    static std::string formatNumber(double value, bool asFraction = false);
    
    // Check if a number is approximately integer
    static bool isApproximatelyInteger(double value, double tolerance = 1e-10);

private:
    static long long findBestFraction(double value, long long maxDenominator = 1000000);
};

#endif 