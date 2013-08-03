#include "Operators.hpp"
#include "Particle.hpp"

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
    
    void TransformP( CompoundParticle & particle ){
	for ( size_t iPart=0; iPart<particle.m_uiNumConstituents; ++iPart ){
	    TransformP( particle.m_apConstituents[ iPart ] );
	}
    }
    
    void TransformC( CompoundParticle & particle ){
	for ( size_t iPart=0; iPart<particle.m_uiNumConstituents; ++iPart ){
	    TransformC( particle.m_apConstituents[ iPart ] );
	}
    }
    
    void TransformT( CompoundParticle & particle ){
	for ( size_t iPart=0; iPart<particle.m_uiNumConstituents; ++iPart ){
	    TransformT( particle.m_apConstituents[ iPart ] );
	}
    }

}
