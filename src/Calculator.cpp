#include "Calculator.h"
#include "Display.h"
#include "BasicOperations.h"
#include "ScientificOperations.h"
#include "MatrixOperations.h"
#include "EquationSolver.h"
#include "ScientificSymbols.h"
#include "NumberFormat.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <complex>

Calculator::Calculator() : currentValue(0), memoryValue(0), displayAsFraction(false) {}

void Calculator::run() {
    std::string input;
    while (true) {
        showMenu();
        std::getline(std::cin, input);
        if (input == "q" || input == "Q") {
            break;
        }
        processInput(input);
        
        // Ask user if they want to continue
        display.showMessage("\nDo you want to continue? (y/n): ");
        std::getline(std::cin, input);
        if (input != "y" && input != "Y") {
            break;
        }
    }
}

void Calculator::showMenu() {
    display.clear();
    display.showMessage("\nCASIO Calculator");
    display.showMessage("Current Value: " + NumberFormat::formatNumber(currentValue, displayAsFraction));
    display.showMessage("\nOperations:");
    display.showMessage("Basic: number [operator] number (e.g., 5 + 3)");
    display.showMessage("Scientific: [function] number (e.g., sin 30)");
    display.showMessage("Memory: MS (store), MR (recall), MC (clear)");
    display.showMessage("H: Show History");
    display.showMessage("Q: Quit");
    display.showMessage("\nMatrix/Vector Operations:");
    display.showMessage("vadd - Add vectors");
    display.showMessage("vsub - Subtract vectors");
    display.showMessage("vdot - Vector dot product");
    display.showMessage("vscalar - Scalar multiplication (vector)");
    display.showMessage("madd - Add matrices");
    display.showMessage("msub - Subtract matrices");
    display.showMessage("mmult - Multiply matrices");
    display.showMessage("mscalar - Scalar multiplication (matrix)");
    display.showMessage("mtrans - Matrix transpose");
    display.showMessage("\nEquation Solving:");
    display.showMessage("quad - Solve quadratic equation (ax² + bx + c = 0)");
    display.showMessage("cubic - Solve cubic equation (ax³ + bx² + cx + d = 0)");
    display.showMessage("quartic - Solve quartic equation (ax⁴ + bx³ + cx² + dx + e = 0)");
    display.showMessage("\nAdvanced Operations:");
    display.showMessage("pow x y - Calculate x raised to power y");
    display.showMessage("root x n - Calculate nth root of x");
    display.showMessage("inv x - Calculate inverse (1/x)");
    display.showMessage("pi - Get value of π");
    display.showMessage("e - Get value of e");
    
    display.showMessage("\nFraction Operations:");
    display.showMessage("fadd n1 d1 n2 d2 - Add fractions (n1/d1 + n2/d2)");
    display.showMessage("fsub n1 d1 n2 d2 - Subtract fractions");
    display.showMessage("fmul n1 d1 n2 d2 - Multiply fractions");
    display.showMessage("fdiv n1 d1 n2 d2 - Divide fractions");
    display.showMessage("\nScientific Constants:");
    display.showMessage("Physical: c, h, k, Na, G, me, mp");
    display.showMessage("Mathematical: pi, e, phi");
    display.showMessage("Usage: '5 * c' for speed of light calculation");
    
    display.showMessage("\nTechnical Symbols:");
    display.showMessage("Greek: alpha, beta, gamma, delta, pi, omega");
    display.showMessage("Math: sqrt, sum, integral, leq, geq, neq");
    display.showMessage("Usage: 'sqrt 16' or 'alpha = 0.05'");
    
    display.showMessage("\nDisplay Format:");
    display.showMessage("format dec - Switch to decimal format");
    display.showMessage("format frac - Switch to fraction format");
    display.showMessage("Current format: " + std::string(displayAsFraction ? "Fraction" : "Decimal"));
    
    display.showMessage("\nEnter command: ");
}

void Calculator::processInput(const std::string& input) {
    try {
        std::vector<std::string> tokens = tokenizeInput(input);
        if (tokens.empty()) return;

        std::string command = tokens[0];

        // Handle format switching
        if (command == "format") {
            if (tokens.size() < 2) {
                throw std::runtime_error("Missing format type");
            }
            if (tokens[1] == "dec") {
                displayAsFraction = false;
                display.showMessage("Switched to decimal format");
            }
            else if (tokens[1] == "frac") {
                displayAsFraction = true;
                display.showMessage("Switched to fraction format");
            }
            else {
                throw std::runtime_error("Invalid format type");
            }
            return;
        }

        // Replace constants and symbols
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (ScientificSymbols::isConstant(tokens[i])) {
                double value = ScientificSymbols::getConstant(tokens[i]);
                tokens[i] = std::to_string(value);
            }
            else if (ScientificSymbols::isSymbol(tokens[i])) {
                tokens[i] = ScientificSymbols::getSymbol(tokens[i]);
            }
        }

        // Memory and History commands
        if (command == "H" || command == "h") {
            showHistory();
            return;
        }
        else if (command == "MS" || command == "MR" || command == "MC") {
            if (command == "MS") storeInMemory();
            else if (command == "MR") recallMemory();
            else clearMemory();
            return;
        }

        // Scientific operations
        if (command == "sin" || command == "cos" || command == "tan") {
            if (tokens.size() < 2) throw std::runtime_error("Missing angle value");
            double angle = std::stod(tokens[1]);
            if (command == "sin") currentValue = scientificOps.sin(angle);
            else if (command == "cos") currentValue = scientificOps.cos(angle);
            else currentValue = scientificOps.tan(angle);
            addToHistory(currentValue);
            displayResult(currentValue);
        }
        // Vector operations
        else if (command == "vadd" || command == "vsub" || command == "vdot" || command == "vscalar") {
            if (command == "vadd") {
                auto v1 = inputVector("Enter first vector:");
                auto v2 = inputVector("Enter second vector:");
                auto result = matrixOps.addVectors(v1, v2);
                displayVector(result);
            }
            else if (command == "vsub") {
                auto v1 = inputVector("Enter first vector:");
                auto v2 = inputVector("Enter second vector:");
                auto result = matrixOps.subtractVectors(v1, v2);
                displayVector(result);
            }
            else if (command == "vdot") {
                auto v1 = inputVector("Enter first vector:");
                auto v2 = inputVector("Enter second vector:");
                currentValue = matrixOps.dotProduct(v1, v2);
                displayResult(currentValue);
                addToHistory(currentValue);
            }
            else if (command == "vscalar") {
                auto v = inputVector("Enter vector:");
                display.showMessage("Enter scalar value:");
                double scalar;
                std::cin >> scalar;
                std::cin.ignore();
                auto result = matrixOps.scalarMultiply(v, scalar);
                displayVector(result);
            }
        }
        // Matrix operations
        else if (command == "madd" || command == "msub" || command == "mmult" || 
                 command == "mscalar" || command == "mtrans") {
            if (command == "madd") {
                auto m1 = inputMatrix("Enter first matrix:");
                auto m2 = inputMatrix("Enter second matrix:");
                auto result = matrixOps.addMatrices(m1, m2);
                displayMatrix(result);
            }
            else if (command == "msub") {
                auto m1 = inputMatrix("Enter first matrix:");
                auto m2 = inputMatrix("Enter second matrix:");
                auto result = matrixOps.subtractMatrices(m1, m2);
                displayMatrix(result);
            }
            else if (command == "mmult") {
                auto m1 = inputMatrix("Enter first matrix:");
                auto m2 = inputMatrix("Enter second matrix:");
                auto result = matrixOps.multiplyMatrices(m1, m2);
                displayMatrix(result);
            }
            else if (command == "mscalar") {
                auto m = inputMatrix("Enter matrix:");
                display.showMessage("Enter scalar value:");
                double scalar;
                std::cin >> scalar;
                std::cin.ignore();
                auto result = matrixOps.scalarMultiply(m, scalar);
                displayMatrix(result);
            }
            else if (command == "mtrans") {
                auto m = inputMatrix("Enter matrix:");
                auto result = matrixOps.transpose(m);
                displayMatrix(result);
            }
        }
        // Equation solving
        else if (command == "quad" || command == "cubic" || command == "quartic") {
            if (command == "quad") {
                display.showMessage("Enter coefficients a, b, c for ax² + bx + c = 0:");
                double a, b, c;
                std::cin >> a >> b >> c;
                std::cin.ignore();
                auto solution = eqSolver.solveQuadratic(a, b, c);
                displayEquationSolution(solution);
            }
            else if (command == "cubic") {
                display.showMessage("Enter coefficients a, b, c, d for ax³ + bx² + cx + d = 0:");
                double a, b, c, d;
                std::cin >> a >> b >> c >> d;
                std::cin.ignore();
                auto solution = eqSolver.solveCubic(a, b, c, d);
                displayEquationSolution(solution);
            }
            else if (command == "quartic") {
                display.showMessage("Enter coefficients a, b, c, d, e for ax⁴ + bx³ + cx² + dx + e = 0:");
                double a, b, c, d, e;
                std::cin >> a >> b >> c >> d >> e;
                std::cin.ignore();
                auto solution = eqSolver.solveQuartic(a, b, c, d, e);
                displayEquationSolution(solution);
            }
        }
        // Basic arithmetic operations
        else if (command == "fadd" || command == "fsub" || command == "fmul" || command == "fdiv") {
            if (tokens.size() < 5) {
                throw std::runtime_error("Invalid fraction operation format");
            }
            Fraction f1(std::stoll(tokens[1]), std::stoll(tokens[2]));
            Fraction f2(std::stoll(tokens[3]), std::stoll(tokens[4]));
            
            Fraction result;
            if (command == "fadd") result = f1.add(f2);
            else if (command == "fsub") result = f1.subtract(f2);
            else if (command == "fmul") result = f1.multiply(f2);
            else result = f1.divide(f2);
            
            currentValue = result.toDouble();
            addToHistory(currentValue);
            display.showMessage("Result: " + result.toString());
        }
        else {
            if (tokens.size() >= 3) {
                double num1 = std::stod(tokens[0]);
                std::string op = tokens[1];
                double num2 = std::stod(tokens[2]);

                if (op == "+") currentValue = basicOps.add(num1, num2);
                else if (op == "-") currentValue = basicOps.subtract(num1, num2);
                else if (op == "*") currentValue = basicOps.multiply(num1, num2);
                else if (op == "/") currentValue = basicOps.divide(num1, num2);
                else throw std::runtime_error("Invalid operator");

                addToHistory(currentValue);
                displayResult(currentValue);
            }
            else {
                throw std::runtime_error("Invalid input format");
            }
        }
    }
    catch (const std::exception& e) {
        display.showError(e.what());
    }
}

void Calculator::storeInMemory() {
    memoryValue = currentValue;
    display.showMessage("Value stored in memory");
}

void Calculator::recallMemory() {
    currentValue = memoryValue;
    display.showMessage("Value recalled from memory");
}

void Calculator::clearMemory() {
    memoryValue = 0;
    display.showMessage("Memory cleared");
}

void Calculator::addToHistory(double result) {
    ansHistory.push_back(result);
    if (ansHistory.size() > 10) {
        ansHistory.erase(ansHistory.begin());
    }
}

void Calculator::showHistory() const {
    display.showMessage("\nCalculation History:");
    for (size_t i = 0; i < ansHistory.size(); ++i) {
        display.showMessage(std::to_string(i + 1) + ": " + 
                          NumberFormat::formatNumber(ansHistory[i], displayAsFraction));
    }
}

// Helper methods implementation
std::vector<double> Calculator::inputVector(const std::string& prompt) {
    display.showMessage(prompt);
    display.showMessage("Enter dimension:");
    int dim;
    std::cin >> dim;
    std::vector<double> v(dim);
    display.showMessage("Enter elements:");
    for (int i = 0; i < dim; ++i) {
        std::cin >> v[i];
    }
    std::cin.ignore(); // Clear newline
    return v;
}

MatrixOperations::Matrix Calculator::inputMatrix(const std::string& prompt) {
    display.showMessage(prompt);
    display.showMessage("Enter rows and columns:");
    int rows, cols;
    std::cin >> rows >> cols;
    MatrixOperations::Matrix m(rows, std::vector<double>(cols));
    display.showMessage("Enter elements row by row:");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> m[i][j];
        }
    }
    std::cin.ignore(); // Clear newline
    return m;
}

void Calculator::displayVector(const std::vector<double>& v) const {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        oss << NumberFormat::formatNumber(v[i], displayAsFraction);
        if (i < v.size() - 1) oss << ", ";
    }
    oss << "]";
    display.showMessage(oss.str());
}

void Calculator::displayMatrix(const MatrixOperations::Matrix& m) const {
    for (const auto& row : m) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            oss << NumberFormat::formatNumber(row[i], displayAsFraction);
            if (i < row.size() - 1) oss << ", ";
        }
        oss << "]";
        display.showMessage(oss.str());
    }
}

void Calculator::displayEquationSolution(const EquationSolver::Solution& solution) {
    display.showMessage("\nRoots:");
    for (size_t i = 0; i < solution.roots.size(); ++i) {
        std::ostringstream oss;
        oss << "x" << (i + 1) << " = ";
        if (solution.hasRealRootsOnly) {
            oss << NumberFormat::formatNumber(solution.roots[i].real(), displayAsFraction);
        } else {
            oss << NumberFormat::formatNumber(solution.roots[i].real(), displayAsFraction);
            if (solution.roots[i].imag() >= 0) {
                oss << " + " << NumberFormat::formatNumber(solution.roots[i].imag(), displayAsFraction) << "i";
            } else {
                oss << " - " << NumberFormat::formatNumber(std::abs(solution.roots[i].imag()), displayAsFraction) << "i";
            }
        }
        display.showMessage(oss.str());
    }
}

// Helper method to tokenize input
std::vector<std::string> Calculator::tokenizeInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void Calculator::displayResult(double value) {
    std::string result = "Result: " + NumberFormat::formatNumber(value, displayAsFraction);
    display.showMessage(result);
}
