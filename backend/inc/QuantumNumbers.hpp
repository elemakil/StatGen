#ifndef QUANTUMNUMBERS_H
#define QUANTUMNUMBERS_H

#include <iostream>

namespace Flavour {
    enum aFlavour {
	Up,
	Down,
	Strange,
	Charm,
	Top,
	Bottom,
    
	AntiUp,
	AntiDown,
	AntiStrange,
	AntiCharm,
	AntiTop,
	AntiBottom
    };
    
    extern const char * Names [];
}

// this function switches a flavour for its C conjugate flavour
inline void SwitchFlavour( Flavour::aFlavour & flavour ){
    flavour = static_cast<Flavour::aFlavour>( ( static_cast<int>( flavour ) + 6 ) % 12 );    
}

namespace Spin {
    enum aSpin {
	Up,
	Down,
	NoSpin
    };
    
    extern const char * Names [];
}    

// this functions switches from spin-up to spin down and vice-versa
inline void SwitchSpin( Spin::aSpin & spin ){
    if ( spin != Spin::NoSpin ){
	spin = static_cast<Spin::aSpin>( ( static_cast<int>( spin ) + 1 ) % 2 );    
    }
}

namespace Colour {
    enum aColour {
	Red,
	Green,
	Blue,
	White,
    
	AntiRed,
	AntiGreen,
	AntiBlue,
	AntiWhite,
	
	NoColour
    };
    
    extern const char * Names [];
}

// this functions switches from colour to anti-colour and vice-versa
inline void SwitchColour( Colour::aColour & colour ){
    if ( colour != Colour::NoColour ){
	colour = static_cast<Colour::aColour>( ( static_cast<int>( colour ) + 4 ) % 8 );    
    }
}

namespace Handedness {
    enum aHandedness {
	Left,
	Right,
	
	NoHandedness
    };
    
    extern const char * Names [];
}

// this functions switches from left-handedness to right-handedness and vice-versa
inline void SwitchHandedness( Handedness::aHandedness & hand ){
    if ( hand != Handedness::NoHandedness ){
	hand = static_cast<Handedness::aHandedness>( ( static_cast<int>( hand ) + 1 ) % 2 );    
    }
}

namespace Type {
    enum aType {
	Fermion,
	Boson
    };
    
    extern const char * Names [];
}

#endif // QUANTUMNUMBERS_H
