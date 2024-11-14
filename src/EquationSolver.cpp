#include "EquationSolver.h"
#include <cmath>
#include <algorithm>

EquationSolver::Solution EquationSolver::solveQuadratic(double a, double b, double c) {
    Solution solution;
    if (a == 0) {
        if (b == 0) {
            throw std::runtime_error("Not a quadratic equation (a = b = 0)");
        }
        // Linear equation: bx + c = 0
        solution.roots.push_back(std::complex<double>(-c / b, 0));
        solution.hasRealRootsOnly = true;
        return solution;
    }

    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double sqrtDisc = std::sqrt(discriminant);
        solution.roots.push_back(std::complex<double>((-b + sqrtDisc) / (2 * a), 0));
        solution.roots.push_back(std::complex<double>((-b - sqrtDisc) / (2 * a), 0));
        solution.hasRealRootsOnly = true;
    } else {
        double realPart = -b / (2 * a);
        double imagPart = std::sqrt(-discriminant) / (2 * a);
        solution.roots.push_back(std::complex<double>(realPart, imagPart));
        solution.roots.push_back(std::complex<double>(realPart, -imagPart));
        solution.hasRealRootsOnly = false;
    }
    return solution;
}

EquationSolver::Solution EquationSolver::solveCubic(double a, double b, double c, double d) {
    Solution solution;
    if (a == 0) {
        return solveQuadratic(b, c, d);
    }

    // Convert to depressed cubic t³ + pt + q = 0
    double p = (3 * a * c - b * b) / (3 * a * a);
    double q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);

    std::complex<double> D = std::complex<double>(q * q / 4 + p * p * p / 27, 0);
    std::complex<double> u = cubicRoot(-q/2 + std::sqrt(D));
    std::complex<double> v = cubicRoot(-q/2 - std::sqrt(D));

    // Roots
    std::complex<double> omega(-0.5, std::sqrt(3)/2);
    std::complex<double> omega2 = omega * omega;

    solution.roots.push_back(u + v - std::complex<double>(b/(3*a), 0));
    solution.roots.push_back(u * omega + v * omega2 - std::complex<double>(b/(3*a), 0));
    solution.roots.push_back(u * omega2 + v * omega - std::complex<double>(b/(3*a), 0));

    // Check if all roots are real
    solution.hasRealRootsOnly = true;
    for (const auto& root : solution.roots) {
        if (!isRealRoot(root)) {
            solution.hasRealRootsOnly = false;
            break;
        }
    }

    return solution;
}

EquationSolver::Solution EquationSolver::solveQuartic(double a, double b, double c, double d, double e) {
    Solution solution;
    if (a == 0) {
        return solveCubic(b, c, d, e);
    }

    // Normalize coefficients
    b /= a; c /= a; d /= a; e /= a;

    // Convert to depressed quartic
    double p = c - 3*b*b/8;
    double q = b*b*b/8 - b*c/2 + d;
    double r = -3*b*b*b*b/256 + b*b*c/16 - b*d/4 + e;

    // Solve resolvent cubic
    Solution resolvent = solveCubic(1, 2*p, p*p-4*r, -q*q);
    
    // Find a real root of the resolvent cubic
    double y = 0;
    for (const auto& root : resolvent.roots) {
        if (isRealRoot(root)) {
            y = root.real();
            break;
        }
    }

    // Calculate square roots
    double R = std::sqrt(2*y + p);
    double D = std::sqrt(y*y + q/R);
    double E = std::sqrt(y*y - q/R);

    // Calculate roots
    solution.roots.push_back(std::complex<double>(-b/4 + (R + D)/2, 0));
    solution.roots.push_back(std::complex<double>(-b/4 + (R - D)/2, 0));
    solution.roots.push_back(std::complex<double>(-b/4 + (-R + E)/2, 0));
    solution.roots.push_back(std::complex<double>(-b/4 + (-R - E)/2, 0));

    // Check if all roots are real
    solution.hasRealRootsOnly = true;
    for (const auto& root : solution.roots) {
        if (!isRealRoot(root)) {
            solution.hasRealRootsOnly = false;
            break;
        }
    }

    return solution;
}

std::complex<double> EquationSolver::cubicRoot(std::complex<double> x) {
    double r = std::abs(x);
    double theta = std::arg(x);
    return std::pow(r, 1.0/3.0) * std::complex<double>(std::cos(theta/3.0), std::sin(theta/3.0));
}

bool EquationSolver::isRealRoot(const std::complex<double>& root, double tolerance) {
    return std::abs(root.imag()) < tolerance;
}

double EquationSolver::findMaxAbs(const std::vector<std::complex<double>>& nums) {
    double maxAbs = 0;
    for (const auto& num : nums) {
        maxAbs = std::max(maxAbs, std::abs(num));
    }
    return maxAbs;
} 