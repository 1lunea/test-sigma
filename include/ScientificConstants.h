#ifndef SCIENTIFIC_CONSTANTS_H
#define SCIENTIFIC_CONSTANTS_H

class ScientificConstants {
public:
    // Physical Constants
    static constexpr double SPEED_OF_LIGHT = 299792458.0;        // m/s
    static constexpr double PLANCK_CONSTANT = 6.62607015e-34;    // J⋅s
    static constexpr double BOLTZMANN_CONSTANT = 1.380649e-23;   // J/K
    static constexpr double AVOGADRO_NUMBER = 6.02214076e23;     // mol^-1
    static constexpr double ELECTRON_MASS = 9.1093837015e-31;    // kg
    static constexpr double PROTON_MASS = 1.67262192369e-27;     // kg
    static constexpr double GRAVITATIONAL_CONSTANT = 6.67430e-11; // m³/(kg⋅s²)
    
    // Mathematical Constants
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double E = 2.71828182845904523536;
    static constexpr double GOLDEN_RATIO = 1.61803398874989484820;
};

#endif 