#include "Particle.hpp"

Particle::Particle( Flavour::aFlavour flavour, Spin::aSpin spin, Colour::aColour colour, Handedness::aHandedness handedness ) : Flavour( flavour ), Spin( spin ), Colour( colour ), Handedness( handedness ){
    
}

/* virtual */ void Particle::Print( std::ostream & aStream /* = std::cout */ ){
    aStream << " |F,C,S,H> = |" << Flavour::Names[ Flavour ] << "," << Colour::Names[ Colour ] << "," << Spin::Names[ Spin ] << "," << Handedness::Names[ Handedness ] << ">" << std::endl;
}

