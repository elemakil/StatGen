#ifndef OPERATORS_H
#define OPERATORS_H

#include "QuantumNumbers.hpp"
#include "Particle.hpp"

namespace Operators {
    void TransformP( Particle * part );
    
    void TransformC( Particle * part );
    
    void TransformT( Particle * part );
}


#endif // OPERATORS_H
