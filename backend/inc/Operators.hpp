#ifndef OPERATORS_H
#define OPERATORS_H

#include "QuantumNumbers.hpp"
#include "Particle.hpp"

namespace Operators {
    void TransformP( Particle & particle );
    
    void TransformC( Particle & particle );
    
    void TransformT( Particle & particle );
}


#endif // OPERATORS_H
