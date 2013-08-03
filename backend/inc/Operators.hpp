#ifndef OPERATORS_H
#define OPERATORS_H

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
    
}

#endif // OPERATORS_H
