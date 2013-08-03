#include "Operators.hpp"

namespace Operators {

    void TransformP( Particle & particle ){
	SwitchHandedness( particle.Handedness );
    }

    void TransformC( Particle & particle ){
	SwitchColour( particle.Colour );
	SwitchFlavour( particle.Flavour );
    }
    
    void TransformT( Particle & particle ){
	SwitchSpin( particle.Spin );
    }
    
}
