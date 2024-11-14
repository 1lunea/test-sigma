#include "ScientificSymbols.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

const std::map<std::string, std::string> ScientificSymbols::SYMBOLS = {
    {"deg", "°"},
    {"alpha", "α"},
    {"beta", "β"},
    {"gamma", "γ"},
    {"delta", "Δ"},
    {"pi", "π"},
    {"mu", "μ"},
    {"omega", "Ω"},
    {"theta", "θ"},
    {"sigma", "σ"},
    {"infinity", "∞"},
    {"plusminus", "±"},
    {"squared", "²"},
    {"cubed", "³"},
    {"sum", "Σ"},
    {"integral", "∫"},
    {"partial", "∂"},
    {"sqrt", "√"},
    {"neq", "≠"},
    {"leq", "≤"},
    {"geq", "≥"}
};

const std::map<std::string, double> ScientificSymbols::CONSTANTS = {
    // Mathematical constants
    {"pi", 3.14159265358979323846},
    {"e", 2.71828182845904523536},
    {"phi", 1.61803398874989484820}, // Golden ratio

    // Physical constants
    {"c", 299792458.0},              // Speed of light (m/s)
    {"h", 6.62607015e-34},           // Planck constant (J⋅s)
    {"k", 1.380649e-23},             // Boltzmann constant (J/K)
    {"Na", 6.02214076e23},           // Avogadro constant (mol^-1)
    {"G", 6.67430e-11},              // Gravitational constant (m³/kg⋅s²)
    {"me", 9.1093837015e-31},        // Electron mass (kg)
    {"mp", 1.67262192369e-27},       // Proton mass (kg)
    {"mu0", 1.25663706212e-6},       // Vacuum permeability (H/m)
    {"eps0", 8.8541878128e-12},      // Vacuum permittivity (F/m)
    {"R", 8.31446261815324},         // Gas constant (J/mol⋅K)
    {"F", 96485.33212},              // Faraday constant (C/mol)
    
    // Astronomical constants
    {"AU", 1.495978707e11},          // Astronomical Unit (m)
    {"ly", 9.4607304725808e15},      // Light year (m)
    {"pc", 3.0856775814913673e16},   // Parsec (m)
    
    // Atomic units
    {"a0", 5.29177210903e-11},       // Bohr radius (m)
    {"Eh", 4.3597447222071e-18}      // Hartree energy (J)
};

std::string ScientificSymbols::getSymbol(const std::string& name) {
    auto it = SYMBOLS.find(name);
    if (it != SYMBOLS.end()) {
        return it->second;
    }
    throw std::runtime_error("Unknown symbol: " + name);
}

double ScientificSymbols::getConstant(const std::string& name) {
    auto it = CONSTANTS.find(name);
    if (it != CONSTANTS.end()) {
        return it->second;
    }
    throw std::runtime_error("Unknown constant: " + name);
}

bool ScientificSymbols::isSymbol(const std::string& name) {
    return SYMBOLS.find(name) != SYMBOLS.end();
}

bool ScientificSymbols::isConstant(const std::string& name) {
    return CONSTANTS.find(name) != CONSTANTS.end();
}

std::string ScientificSymbols::formatScientific(double value, int precision) {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(precision) << value;
    return oss.str();
} 