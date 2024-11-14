#ifndef FRACTION_H
#define FRACTION_H

#include <string>

class Fraction {
public:
    Fraction(long long numerator = 0, long long denominator = 1);
    
    // Basic operations
    Fraction add(const Fraction& other) const;
    Fraction subtract(const Fraction& other) const;
    Fraction multiply(const Fraction& other) const;
    Fraction divide(const Fraction& other) const;
    
    // Utility methods
    void reduce();
    double toDouble() const;
    std::string toString() const;
    
    // Getters
    long long getNumerator() const { return numerator; }
    long long getDenominator() const { return denominator; }

private:
    long long numerator;
    long long denominator;
    
    static long long gcd(long long a, long long b);
    static long long lcm(long long a, long long b);
};

#endif 