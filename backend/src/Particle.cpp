#include "Particle.hpp"

//////////////////////////////////////////////////////////////////////
// PARTICLE CLASS MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////

Particle::Particle(){
    Flavour = Flavour::Up;
    Spin = Spin::NoSpin;
    Colour = Colour::NoColour;
    Handedness = Handedness::NoHandedness;
    AngularMomentum = 0;
    Type = Type::Fermion;
}

Particle::Particle( Flavour::aFlavour flavour, Spin::aSpin spin, Colour::aColour colour, Handedness::aHandedness handedness, int angularMomentum /* = 0 */, Type::aType type /* = Type::Fermion */ ) : Flavour( flavour ), Spin( spin ), Colour( colour ), Handedness( handedness ), AngularMomentum( angularMomentum ), Type( type ) {
    
}

/* virtual */ void Particle::Print( std::ostream & aStream /* = std::cout */ ){
    aStream << " |F,C,S,H> = |" << Flavour::GetName( Flavour ) << "," << Colour::Names[ Colour ] << "," << Spin::Names[ Spin ] << "," << Handedness::Names[ Handedness ] << "> (is a " << Type::Names[ Type ] << ")" << std::endl;
}


/* virtual */ void Particle::HTMLPrint( std::ostream & aStream /* = std::cout */ ){
    aStream << "|" << Flavour::GetName( Flavour );
    if (Colour!=Colour::NoColour) 
	aStream << "," << Colour::Names[ Colour ];
    if (Spin!=Spin::NoSpin) 
	aStream << "," << Spin::Names[ Spin ];
    if (Handedness!=Handedness::NoHandedness) 
	aStream << "," << Handedness::Names[ Handedness ];
    aStream << "&gt;"  << std::flush;
}

//////////////////////////////////////////////////////////////////////
// COMPOUNTPARTICLE CLASS MEMBER FUNCTIONS
//////////////////////////////////////////////////////////////////////

CompoundParticle::CompoundParticle( unsigned int uiNumConstituents ) : m_uiNumConstituents( uiNumConstituents ) {
    m_apConstituents = new Particle [ uiNumConstituents ];
}
/* virtual */ CompoundParticle::~CompoundParticle(){
    delete [] m_apConstituents;
}

/* virtual */ void CompoundParticle::SetConstituent( unsigned int index, const Particle & particle ){
    if ( index >= m_uiNumConstituents ){
	std::cerr << "ERROR: Index " << index << " not known for this CompoundParticle!" << std::endl;
	return;
    }
    
    m_apConstituents[ index ] = particle;
}

/* virtual */ void CompoundParticle::Print( std::ostream & aStream /* = std::cout */ ){
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	m_apConstituents[ iPart ].Print(aStream);
    }
}


/* virtual */ void CompoundParticle::HTMLPrint( std::ostream & aStream /* = std::cout */ ){
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	if (iPart > 0)
	    aStream << "⊗";
	m_apConstituents[ iPart ].HTMLPrint(aStream);
    }
}

/* virtual */ void CompoundParticle::PrintShort( std::ostream & aStream /* = std::cout */ ){
    std::string sFlavour;
    std::string sColour;
    std::string sSpin;
    std::string sHandedness;
    
    bool bHasColour = true;
    bool bHasSpin = true;
    bool bHasHandedness = true;
    
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	sFlavour += Flavour::GetName( m_apConstituents[ iPart ].Flavour );
	sColour += Colour::KNames[ m_apConstituents[ iPart ].Colour ];
	sSpin += Spin::KNames[ m_apConstituents[ iPart ].Spin ];
	sHandedness += Handedness::KNames[ m_apConstituents[ iPart ].Handedness ];
	
	if ( m_apConstituents[ iPart ].Colour == Colour::NoColour ){
	    bHasColour = false;
	}
	if ( m_apConstituents[ iPart ].Spin == Spin::NoSpin ){
	    bHasSpin = false;
	}
	if ( m_apConstituents[ iPart ].Handedness == Handedness::NoHandedness ){
	    bHasHandedness = false;
	}
    }
    
    aStream << "|" << sFlavour << ">";
    if ( bHasSpin ) { aStream << "|" << sSpin << ">"; }
    if ( bHasColour ) { aStream << "|" << sColour << ">"; }
    if ( bHasHandedness ) { aStream << "|" << sHandedness << ">"; }
}

/* virtual */ std::string CompoundParticle::GetHTMLColour(){
    if ( IsColourNeutral() ){
		return std::string( "444444" );
    }
    else {
		int hColour = 0;
		int red = 0, green = 0, blue = 0;
		auto ac = GetAbsoluteColor();
		red += ac.red * 0x33;
		green += ac.green * 0x33;
		blue += ac.blue * 0x33;
		while (red < 0 || green < 0 || blue < 0 || !(red || green || blue))
		{
			red += 0x33;
			green += 0x33;
			blue += 0x33;
		}
		int maxc = std::max(red,std::max(green,blue));
		if (maxc > 0xff)
		{
			red = (red * 0xff) / maxc;
			green = (green * 0xff) / maxc;
			blue = (blue * 0xff) / maxc;
		}
		
		hColour = std::min(red,0xff)   * 0x010000
				+ std::min(green,0xff) * 0x000100
				+ std::min(blue,0xff)  * 0x000001;
		std::stringstream ss;
		ss << std::hex << std::setw( 6 ) << std::setfill( '0' ) << hColour;
		return ss.str();
    }
}


/* virtual */ float CompoundParticle::GetTotalSpin(){
    float spinSum = 0.0;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	if ( m_apConstituents[ iPart ].Type == Type::Fermion ){
	    if ( m_apConstituents[ iPart ].Spin == Spin::Up ){
		spinSum += 0.5;
	    }
	    if ( m_apConstituents[ iPart ].Spin == Spin::Down ){
		spinSum -= 0.5;
	    }
	}
	if ( m_apConstituents[ iPart ].Type == Type::Boson ){
	    if ( m_apConstituents[ iPart ].Spin == Spin::Up ){
		spinSum += 1.0;
	    }
	    if ( m_apConstituents[ iPart ].Spin == Spin::Down ){
		spinSum -= 1.0;
	    }
	}
    }
    return spinSum;
}

/* virtual */ int CompoundParticle::GetTotalAngularMomentum(){
    int angSum = 0;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	angSum += m_apConstituents[ iPart ].AngularMomentum;
    }
    return angSum;
}

/* virtual */ bool CompoundParticle::IsColourNeutral(){
	AbsoluteColour nums = GetAbsoluteColor();
    if ( nums.red == nums.green && nums.red == nums.blue ){
		return true;
    }
    else {
		return false;
    }
}

/* virtual */ std::string CompoundParticle::GetFlavours(){
    std::string sReturn;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	sReturn += Flavour::GetName( m_apConstituents[ iPart ].Flavour );
    }    
    return sReturn;
}

std::string CompoundParticle::GetFlavoursSorted()
{
    std::string sReturn = GetFlavours();
	std::sort(sReturn.begin(),sReturn.end());
    return sReturn;
}

/* virtual */ std::string CompoundParticle::GetColours(){
    std::string sReturn;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
		sReturn += Colour::KNames[ m_apConstituents[ iPart ].Colour ];
    }    
    return sReturn;
}

AbsoluteColour CompoundParticle::GetAbsoluteColor(){
    int numRed = 0;
    int numGreen = 0;
    int numBlue = 0;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
		if ( m_apConstituents[ iPart ].Colour == Colour::Red ){
			++numRed;
		}
		if ( m_apConstituents[ iPart ].Colour == Colour::AntiRed ){
			--numRed;
		}
		if ( m_apConstituents[ iPart ].Colour == Colour::Green ){
			++numGreen;
		}
		if ( m_apConstituents[ iPart ].Colour == Colour::AntiGreen ){
			--numGreen;
		}
		if ( m_apConstituents[ iPart ].Colour == Colour::Blue ){
			++numBlue;
		}
		if ( m_apConstituents[ iPart ].Colour == Colour::AntiBlue ){
			--numBlue;
		}
    }	
    return {numRed, numGreen, numBlue};
}

/* virtual */ std::string CompoundParticle::GetSpins(){
    std::string sReturn;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	sReturn += Spin::Names[ m_apConstituents[ iPart ].Spin ];
    }    
    return sReturn;
}

int CompoundParticle::GetAbsoluteSpin() { // STUB
	return 0;
}

/* virtual */ std::string CompoundParticle::GetHandednesses(){
    std::string sReturn;
    for ( size_t iPart=0; iPart<m_uiNumConstituents; ++iPart ){
	sReturn += Handedness::Names[ m_apConstituents[ iPart ].Handedness ];
    }    
    return sReturn;
}
