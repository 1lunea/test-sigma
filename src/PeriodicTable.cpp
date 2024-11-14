#include "PeriodicTable.h"
#include <stdexcept>
#include <cctype>

PeriodicTable::PeriodicTable() {
    initializeElements();
}

void PeriodicTable::initializeElements() {
    // This is a simplified version. In practice, you'd want to load this from a file
    elements["H"] = {"H", "Hydrogen", 1, 1.008, "Nonmetal", 1, 1};
    elements["He"] = {"He", "Helium", 2, 4.003, "Noble Gas", 1, 18};
    elements["Li"] = {"Li", "Lithium", 3, 6.941, "Alkali Metal", 2, 1};
    elements["Be"] = {"Be", "Beryllium", 4, 9.012, "Alkaline Earth Metal", 2, 2};
    elements["B"] = {"B", "Boron", 5, 10.811, "Metalloid", 2, 13};
    elements["C"] = {"C", "Carbon", 6, 12.011, "Nonmetal", 2, 14};
    elements["N"] = {"N", "Nitrogen", 7, 14.007, "Nonmetal", 2, 15};
    elements["O"] = {"O", "Oxygen", 8, 15.999, "Nonmetal", 2, 16};
    // Add more elements as needed
}

Element PeriodicTable::getElementBySymbol(const std::string& symbol) {
    auto it = elements.find(symbol);
    if (it == elements.end()) {
        throw std::runtime_error("Element not found: " + symbol);
    }
    return it->second;
}

Element PeriodicTable::getElementByNumber(int atomicNumber) {
    for (const auto& pair : elements) {
        if (pair.second.atomicNumber == atomicNumber) {
            return pair.second;
        }
    }
    throw std::runtime_error("Element not found with atomic number: " + std::to_string(atomicNumber));
}

Element PeriodicTable::getElementByName(const std::string& name) {
    for (const auto& pair : elements) {
        if (pair.second.name == name) {
            return pair.second;
        }
    }
    throw std::runtime_error("Element not found: " + name);
}

std::map<std::string, int> PeriodicTable::parseFormula(const std::string& formula) {
    std::map<std::string, int> composition;
    std::string currentElement;
    std::string currentNumber;
    
    for (size_t i = 0; i < formula.length(); ++i) {
        if (std::isupper(formula[i])) {
            if (!currentElement.empty()) {
                int count = currentNumber.empty() ? 1 : std::stoi(currentNumber);
                composition[currentElement] += count;
            }
            currentElement = formula[i];
            currentNumber.clear();
        }
        else if (std::islower(formula[i])) {
            currentElement += formula[i];
        }
        else if (std::isdigit(formula[i])) {
            currentNumber += formula[i];
        }
    }
    
    if (!currentElement.empty()) {
        int count = currentNumber.empty() ? 1 : std::stoi(currentNumber);
        composition[currentElement] += count;
    }
    
    return composition;
}

double PeriodicTable::getMolarMass(const std::string& formula) {
    auto composition = parseFormula(formula);
    double molarMass = 0.0;
    
    for (const auto& pair : composition) {
        molarMass += getElementBySymbol(pair.first).atomicMass * pair.second;
    }
    
    return molarMass;
} 