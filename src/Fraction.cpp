#include "Fraction.h"
#include <stdexcept>
#include <cmath>
#include <sstream>

Fraction::Fraction(long long num, long long den) : numerator(num), denominator(den) {
    if (denominator == 0) {
        throw std::runtime_error("Denominator cannot be zero!");
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    reduce();
}

Fraction Fraction::add(const Fraction& other) const {
    long long lcm_val = lcm(denominator, other.denominator);
    long long num = numerator * (lcm_val / denominator) + 
                    other.numerator * (lcm_val / other.denominator);
    return Fraction(num, lcm_val);
}

Fraction Fraction::subtract(const Fraction& other) const {
    long long lcm_val = lcm(denominator, other.denominator);
    long long num = numerator * (lcm_val / denominator) - 
                    other.numerator * (lcm_val / other.denominator);
    return Fraction(num, lcm_val);
}

Fraction Fraction::multiply(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::divide(const Fraction& other) const {
    if (other.numerator == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

void Fraction::reduce() {
    long long gcd_val = gcd(std::abs(numerator), denominator);
    numerator /= gcd_val;
    denominator /= gcd_val;
}

double Fraction::toDouble() const {
    return static_cast<double>(numerator) / denominator;
}

std::string Fraction::toString() const {
    std::ostringstream oss;
    if (denominator == 1) {
        oss << numerator;
    } else {
        oss << numerator << "/" << denominator;
    }
    return oss.str();
}

long long Fraction::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long Fraction::lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
} 