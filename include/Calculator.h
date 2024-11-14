#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Display.h"
#include "BasicOperations.h"
#include "ScientificOperations.h"
#include "MatrixOperations.h"
#include "EquationSolver.h"
#include "ScientificSymbols.h"
#include "NumberFormat.h"
#include <vector>
#include <string>
#include <complex>

class Calculator {
private:
    double currentValue;
    double memoryValue;
    std::vector<double> ansHistory;
    Display display;
    BasicOperations basicOps;
    ScientificOperations scientificOps;
    MatrixOperations matrixOps;
    EquationSolver eqSolver;
    bool displayAsFraction;
    NumberFormat numberFormat;

    void storeInMemory();
    void recallMemory();
    void clearMemory();
    void addToHistory(double result);
    void showHistory() const;
    
    // Helper methods
    std::vector<std::string> tokenizeInput(const std::string& input);
    std::vector<double> inputVector(const std::string& prompt);
    MatrixOperations::Matrix inputMatrix(const std::string& prompt);
    void displayVector(const std::vector<double>& v) const;
    void displayMatrix(const MatrixOperations::Matrix& m) const;
    void displayEquationSolution(const EquationSolver::Solution& solution);

public:
    Calculator();
    void run();
    void showMenu();
    void processInput(const std::string& input);
};

#endif 