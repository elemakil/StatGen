#include "InputParser.hpp"

InputParser::InputParser( std::string sInput ) : m_sInput( sInput ){
    
}

/* virtual */ InputParser::~InputParser(){
    
}

// Do basic checks of the syntax of the user input
// checks for:
//   - unmatched parentheses
//   - correct Ket notation
/* virtual */ bool InputParser::m_fCheckSyntax(){
    size_t uiCountOpenParen = std::count( m_sInput.begin(), m_sInput.end(), '(' );
    size_t uiCountCloseParen = std::count( m_sInput.begin(), m_sInput.end(), ')' );
    
    if ( uiCountOpenParen != uiCountCloseParen ){
	std::cerr << "ERROR: Unmatched number of parentheses!" << std::endl;
	return false;
    }
    
    size_t uiCountOpenKet = std::count( m_sInput.begin(), m_sInput.end(), '|' );
    size_t uiCountCloseKet = std::count( m_sInput.begin(), m_sInput.end(), '>' );
    
    if ( uiCountOpenKet != uiCountCloseKet ){
	std::cerr << "ERROR: Unmatched Ket-Notation!" << std::endl;
	return false;
    }
    
    // By default return true
    return true;
}
