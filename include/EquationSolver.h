#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H

#include <vector>
#include <complex>

class EquationSolver {
public:
    struct Solution {
        std::vector<std::complex<double>> roots;
        bool hasRealRootsOnly;
    };

    // Solves ax² + bx + c = 0
    Solution solveQuadratic(double a, double b, double c);

    // Solves ax³ + bx² + cx + d = 0
    Solution solveCubic(double a, double b, double c, double d);

    // Solves ax⁴ + bx³ + cx² + dx + e = 0
    Solution solveQuartic(double a, double b, double c, double d, double e);

private:
    // Helper methods
    std::complex<double> cubicRoot(std::complex<double> x);
    double findMaxAbs(const std::vector<std::complex<double>>& nums);
    bool isRealRoot(const std::complex<double>& root, double tolerance = 1e-10);
};

#endif 