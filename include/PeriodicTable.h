#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include <string>
#include <map>

struct Element {
    std::string symbol;
    std::string name;
    int atomicNumber;
    double atomicMass;
    std::string category;
    int period;
    int group;
};

class PeriodicTable {
public:
    PeriodicTable();
    
    Element getElementBySymbol(const std::string& symbol);
    Element getElementByNumber(int atomicNumber);
    Element getElementByName(const std::string& name);
    
    double getMolarMass(const std::string& formula);

private:
    std::map<std::string, Element> elements;
    void initializeElements();
    std::map<std::string, int> parseFormula(const std::string& formula);
};

#endif 