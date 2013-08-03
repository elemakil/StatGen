#ifndef OPERATORS_H
#define OPERATORS_H

#include <algorithm>

#include "QuantumNumbers.hpp"

class Particle;
class CompoundParticle;

namespace Operators {
    //////////////////////////////////////////////////////////////////////
    // Perform Discrete Transformation on elementary particles
    void TransformP( Particle & particle );
    void TransformC( Particle & particle );
    void TransformT( Particle & particle );
    
    //////////////////////////////////////////////////////////////////////
    // Perform Discrete Transformation on compound particles
    void TransformC( CompoundParticle & particle );
    void TransformP( CompoundParticle & particle );
    void TransformT( CompoundParticle & particle );
    
    //////////////////////////////////////////////////////////////////////
    // swap quantum numbers of elementary particles
    void SwapSpin( Particle & firstParticle, Particle & secondParticle );
    void SwapColour( Particle & firstParticle, Particle & secondParticle );
    void SwapFlavour( Particle & firstParticle, Particle & secondParticle );
    void SwapHandedness( Particle & firstParticle, Particle & secondParticle );

    //////////////////////////////////////////////////////////////////////
    // swap quantum numbers of two constituents of compound particle
    void SwapSpin( CompoundParticle & particle, unsigned int i, unsigned int j );
    void SwapColour( CompoundParticle & particle, unsigned int i, unsigned int j );
    void SwapFlavour( CompoundParticle & particle, unsigned int i, unsigned int j );
    void SwapHandedness( CompoundParticle & particle, unsigned int i, unsigned int j );
}

#endif // OPERATORS_H
