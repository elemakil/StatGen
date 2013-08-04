#ifndef PARTICLE_H
#define PARTICLE_H

#include <ostream>
#include <iostream>

#include "QuantumNumbers.hpp"
#include "Operators.hpp"

class AbstractParticle {
public:
    virtual void Print( std::ostream & aStream = std::cout ) = 0;
	virtual void HTMLPrint( std::ostream & aStream = std::cout ) = 0;
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
    virtual void HTMLPrint( std::ostream & aStream = std::cout );
};

class CompoundParticle : public AbstractParticle {
public:
    CompoundParticle( unsigned int uiNumConstituents );
    virtual ~CompoundParticle();
    
    virtual void SetConstituent( unsigned int index, const Particle & particle );
    virtual inline const Particle & ReadConstituent( unsigned int index );
    virtual inline Particle & GetConstituent( unsigned int index );
    
    virtual void Print( std::ostream & aStream = std::cout );
    virtual void HTMLPrint( std::ostream & aStream = std::cout );
    virtual void PrintShort( std::ostream & aStream = std::cout );
    
    virtual float GetTotalSpin();
    virtual int GetTotalAngularMomentum();
    virtual bool IsColourNeutral();
    
    virtual inline unsigned int GetNumConstituents() const { return m_uiNumConstituents; }
    
    friend void Operators::TransformC( CompoundParticle & particle );
    friend void Operators::TransformP( CompoundParticle & particle );
    friend void Operators::TransformT( CompoundParticle & particle );
private:
    unsigned int m_uiNumConstituents;
    Particle * m_apConstituents;
};

/* virtual inline */ const Particle & CompoundParticle::ReadConstituent( unsigned int index ){
    if ( index >= m_uiNumConstituents ){
	std::cerr << "ERROR: Index " << index << " not known for this CompoundParticle!" << std::endl;
	return m_apConstituents[ 0 ];
    }
    
    return m_apConstituents[ index ];
}

/* virtual inline */ Particle & CompoundParticle::GetConstituent( unsigned int index ){
    if ( index >= m_uiNumConstituents ){
	std::cerr << "ERROR: Index " << index << " not known for this CompoundParticle!" << std::endl;
	return m_apConstituents[ 0 ];
    }
    
    return m_apConstituents[ index ];
}


#endif // PARTICLE_H
