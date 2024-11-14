#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <vector>

class Probability {
public:
    // Basic probability calculations
    double probability(int favorableOutcomes, int totalOutcomes);
    double conditionalProbability(double eventA, double eventB, double eventAandB);
    
    // Combinations and Permutations
    long long factorial(int n);
    long long permutation(int n, int r);
    long long combination(int n, int r);
    
    // Distributions
    double binomialProbability(int n, int k, double p);
    double poissonProbability(double lambda, int k);
    double normalDistribution(double x, double mean, double stdDev);
    
    // Statistical measures
    double mean(const std::vector<double>& data);
    double median(const std::vector<double>& data);
    double standardDeviation(const std::vector<double>& data);
    double variance(const std::vector<double>& data);
};

#endif 