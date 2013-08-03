#include "Operators.hpp"

#include "Particle.hpp"

namespace Operators {

    //////////////////////////////////////////////////////////////////////
    // Perform Discrete Transformation on elementary particles
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

    //////////////////////////////////////////////////////////////////////
    // Perform Discrete Transformation on compound particles
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

    //////////////////////////////////////////////////////////////////////
    // swap quantum numbers of elementary particles
    void SwapSpin( Particle & firstParticle, Particle & secondParticle ){
	std::swap( firstParticle.Spin, secondParticle.Spin );
    }
    
    void SwapColour( Particle & firstParticle, Particle & secondParticle ){
	std::swap( firstParticle.Colour, secondParticle.Colour );
    }
    
    void SwapFlavour( Particle & firstParticle, Particle & secondParticle ){
	std::swap( firstParticle.Flavour, secondParticle.Flavour );
    }
    
    void SwapHandedness( Particle & firstParticle, Particle & secondParticle ){
	std::swap( firstParticle.Handedness, secondParticle.Handedness );
    }

    //////////////////////////////////////////////////////////////////////
    // swap quantum numbers of two constituents of compound particle
    void SwapSpin( CompoundParticle & particle, unsigned int i, unsigned int j ){
	if ( i >= particle.GetNumConstituents() || j >= particle.GetNumConstituents() ){
	    std::cerr << "ERROR: Index " << i << " or index " << j << " not known for this CompoundParticle!" << std::endl;
	    return;
	}
	std::swap( particle.GetConstituent( i ).Spin, particle.GetConstituent( j ).Spin );
    }
    
    void SwapColour( CompoundParticle & particle, unsigned int i, unsigned int j ){
	if ( i >= particle.GetNumConstituents() || j >= particle.GetNumConstituents() ){
	    std::cerr << "ERROR: Index " << i << " or index " << j << " not known for this CompoundParticle!" << std::endl;
	    return;
	}
	std::swap( particle.GetConstituent( i ).Colour, particle.GetConstituent( j ).Colour );
    }
    
    void SwapFlavour( CompoundParticle & particle, unsigned int i, unsigned int j ){
	if ( i >= particle.GetNumConstituents() || j >= particle.GetNumConstituents() ){
	    std::cerr << "ERROR: Index " << i << " or index " << j << " not known for this CompoundParticle!" << std::endl;
	    return;
	}
	std::swap( particle.GetConstituent( i ).Flavour, particle.GetConstituent( j ).Flavour );
    }
    
    void SwapHandedness( CompoundParticle & particle, unsigned int i, unsigned int j ){
	if ( i >= particle.GetNumConstituents() || j >= particle.GetNumConstituents() ){
	    std::cerr << "ERROR: Index " << i << " or index " << j << " not known for this CompoundParticle!" << std::endl;
	    return;
	}
	std::swap( particle.GetConstituent( i ).Handedness, particle.GetConstituent( j ).Handedness );
    }
}
