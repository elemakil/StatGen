#ifndef QUANTUMNUMBERS_H
#define QUANTUMNUMBERS_H

#include <utility>
#include <cmath>

namespace Flavour {
    enum aFlavour {
	Down = 1,
	Up = 2,
	Strange = 3,
	Charm = 4,
	Bottom = 5,
	Top = 6,
    
	AntiDown = -1,
	AntiUp = -2,
	AntiStrange = -3,
	AntiCharm = -4,
	AntiBottom = -5,
	AntiTop = -6
    };
    
    extern const char * Names [];
    extern const char * UNames [];
    
    const char * GetName( int index );
    const char * GetUName( int index );
}

// this function switches a flavour for its C conjugate flavour
inline void SwitchFlavour( Flavour::aFlavour & flavour ){
    flavour = static_cast<Flavour::aFlavour>( -1 * static_cast<int>( flavour ) );    
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
    extern const char * KNames [];
    extern const char * FileNames [];
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

namespace QuantumNumber {
    enum aQuantumNumber {
	Flavour,
	Colour,
	Spin,
	Handedness,
	
	Error
    };
    
    union uQuantumNumber {
	Flavour::aFlavour Flavour;
	Colour::aColour Colour;
	Spin::aSpin Spin;
	Handedness::aHandedness Handedness;
    };

    std::pair<aQuantumNumber,uQuantumNumber> GetFromChar( char cData );
}


#endif // QUANTUMNUMBERS_H
