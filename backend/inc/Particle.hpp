#ifndef PARTICLE_H
#define PARTICLE_H

#include <ostream>

#include "QuantumNumbers.hpp"

class Particle {
public:
    Particle( Flavour::aFlavour flavour, Spin::aSpin spin, Colour::aColour colour, Handedness::aHandedness handedness );
    
    Flavour::aFlavour Flavour;
    Spin::aSpin Spin;
    Colour::aColour Colour;
    Handedness::aHandedness Handedness;
    
    virtual void Print( std::ostream & aStream = std::cout );
};

#endif // PARTICLE_H
