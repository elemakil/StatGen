#include "Operators.hpp"

namespace Operators {

    void TransformP( Particle * part ){
	SwitchHandedness( part->Handedness );
    }

    void TransformC( Particle * part ){
	SwitchColour( part->Colour );
	SwitchFlavour( part->Flavour );
    }
    
    void TransformT( Particle * part ){
	SwitchSpin( part->Spin );
    }
    
}
