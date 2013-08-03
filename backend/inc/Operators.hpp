#ifndef OPERATORS_H
#define OPERATORS_H

#include <algorithm>

#include "QuantumNumbers.hpp"

class Particle;
class CompoundParticle;

namespace Operators {

    void TransformP( Particle & particle );
    void TransformC( Particle & particle );
    void TransformT( Particle & particle );

    void TransformC( CompoundParticle & particle );
    void TransformP( CompoundParticle & particle );
    void TransformT( CompoundParticle & particle );
    
    void SwapSpin( Particle & firstParticle, Particle & secondParticle );
    void SwapColour( Particle & firstParticle, Particle & secondParticle );
    void SwapFlavour( Particle & firstParticle, Particle & secondParticle );
    void SwapHandedness( Particle & firstParticle, Particle & secondParticle );
    
}

#endif // OPERATORS_H
