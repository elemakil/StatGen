#ifndef PARTICLE_H
#define PARTICLE_H

#include <ostream>
#include <iostream>

#include "QuantumNumbers.hpp"
#include "Operators.hpp"

class AbstractParticle {
public:
    virtual void Print( std::ostream & aStream = std::cout ) = 0;
};

class Particle : public AbstractParticle {
public:
    Particle();
    
    Particle( Flavour::aFlavour flavour, Spin::aSpin spin, Colour::aColour colour, Handedness::aHandedness handedness, int angularMomentum = 0, Type::aType type = Type::Fermion );
    
    Flavour::aFlavour Flavour;
    Spin::aSpin Spin;
    Colour::aColour Colour;
    Handedness::aHandedness Handedness;
    int AngularMomentum;
    Type::aType Type;
    
    virtual void Print( std::ostream & aStream = std::cout );
};

class CompoundParticle : public AbstractParticle {
public:
    CompoundParticle( unsigned int uiNumConstituents );
    virtual ~CompoundParticle();
    
    virtual void SetConstituent( unsigned int index, const Particle & particle );
    
    virtual void Print( std::ostream & aStream = std::cout );
    
    virtual float GetTotalSpin();
    virtual int GetTotalAngularMomentum();
    virtual bool IsColourNeutral();
    
    friend void Operators::TransformC( CompoundParticle & particle );
    friend void Operators::TransformP( CompoundParticle & particle );
    friend void Operators::TransformT( CompoundParticle & particle );
private:
    unsigned int m_uiNumConstituents;
    Particle * m_apConstituents;
};

#endif // PARTICLE_H
