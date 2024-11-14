#include "Probability.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

double Probability::probability(int favorableOutcomes, int totalOutcomes) {
    if (totalOutcomes <= 0) {
        throw std::runtime_error("Total outcomes must be positive");
    }
    if (favorableOutcomes < 0 || favorableOutcomes > totalOutcomes) {
        throw std::runtime_error("Invalid number of favorable outcomes");
    }
    return static_cast<double>(favorableOutcomes) / totalOutcomes;
}

double Probability::conditionalProbability(double eventA, double eventB, double eventAandB) {
    if (eventB == 0) {
        throw std::runtime_error("Probability of event B cannot be zero");
    }
    return eventAandB / eventB;
}

long long Probability::factorial(int n) {
    if (n < 0) {
        throw std::runtime_error("Factorial undefined for negative numbers");
    }
    if (n > 20) { // Prevent overflow
        throw std::runtime_error("Number too large for factorial calculation");
    }
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long long Probability::permutation(int n, int r) {
    if (n < r || n < 0 || r < 0) {
        throw std::runtime_error("Invalid parameters for permutation");
    }
    return factorial(n) / factorial(n - r);
}

long long Probability::combination(int n, int r) {
    if (n < r || n < 0 || r < 0) {
        throw std::runtime_error("Invalid parameters for combination");
    }
    return factorial(n) / (factorial(r) * factorial(n - r));
}

double Probability::binomialProbability(int n, int k, double p) {
    if (p < 0 || p > 1) {
        throw std::runtime_error("Probability must be between 0 and 1");
    }
    return combination(n, k) * std::pow(p, k) * std::pow(1 - p, n - k);
}

double Probability::poissonProbability(double lambda, int k) {
    if (lambda <= 0) {
        throw std::runtime_error("Lambda must be positive");
    }
    return std::exp(-lambda) * std::pow(lambda, k) / factorial(k);
}

double Probability::normalDistribution(double x, double mean, double stdDev) {
    const double PI = 3.14159265358979323846;
    double exponent = -0.5 * std::pow((x - mean) / stdDev, 2);
    return (1.0 / (stdDev * std::sqrt(2 * PI))) * std::exp(exponent);
}

double Probability::mean(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::runtime_error("Cannot calculate mean of empty dataset");
    }
    double sum = 0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

double Probability::median(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::runtime_error("Cannot calculate median of empty dataset");
    }
    std::vector<double> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    if (sorted.size() % 2 == 0) {
        return (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2;
    }
    return sorted[sorted.size()/2];
}

double Probability::variance(const std::vector<double>& data) {
    if (data.size() < 2) {
        throw std::runtime_error("Need at least 2 values for variance");
    }
    double m = mean(data);
    double sum = 0;
    for (double value : data) {
        sum += std::pow(value - m, 2);
    }
    return sum / (data.size() - 1); // Sample variance
}

double Probability::standardDeviation(const std::vector<double>& data) {
    return std::sqrt(variance(data));
} 