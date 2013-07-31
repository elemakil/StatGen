#include "InputParser.hpp"

InputParser::InputParser( std::string sInput ) : m_sInput( sInput ){
    
}

/* virtual */ InputParser::~InputParser(){
    
}

// Do basic checks of the syntax of the user input
// checks for:
//   - unmatched parentheses
//   - correct Ket notation
//   - opening and closing parentheses are correctly matched, i.e. nothing like "( ) ) ("
/* virtual */ bool InputParser::m_fCheckSyntax(){
    
    // OLD CODE -> Now moved to the bottom and is done in a different way
    // size_t uiCountOpenParen = std::count( m_sInput.begin(), m_sInput.end(), '(' );
    // size_t uiCountCloseParen = std::count( m_sInput.begin(), m_sInput.end(), ')' );
    
    // if ( uiCountOpenParen != uiCountCloseParen ){
    // 	std::cerr << "ERROR: Unmatched number of parentheses!" << std::endl;
    // 	return false;
    // }
    
    size_t uiCountOpenKet = std::count( m_sInput.begin(), m_sInput.end(), '|' );
    size_t uiCountCloseKet = std::count( m_sInput.begin(), m_sInput.end(), '>' );
    
    if ( uiCountOpenKet != uiCountCloseKet ){
	std::cerr << "ERROR: Unmatched Ket-Notation!" << std::endl;
	return false;
    }
    
    unsigned int uiNumOpenParens = 0;
    for ( size_t iChar=0; iChar<m_sInput.size(); ++iChar ){
	if ( m_sInput[ iChar ] == "(" ){
	    ++uiNumOpenParens;
	}
	if ( m_sInput[ iChar ] == ")" ){
	    if ( uiNumOpenParens == 0 ){
		std::cerr << "ERROR: Wrong order of parentheses!" << std::endl;
		return false;
	    }
	    else {
		--uiNumOpenParens;
	    }
	}
    }
    if ( uiNumOpenParens != 0 ){
	std::cerr << "ERROR: Unmatched parenthesis!" << std::endl;
	return false;
    }
    
    // By default return true
    return true;
}
