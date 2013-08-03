#include "CookieParser.hpp"

CookieParser::CookieParser( char * cookies ){
    std::vector<std::string> vsCookies = Split( std::string( cookies ), ';' );
    for ( size_t iCookie=0; iCookie<vsCookies.size(); ++iCookie ){
	auto splitPos = vsCookies.at( iCookie ).find( "=" );
	std::string sKey = vsCookies.at( iCookie ).substr( 0, splitPos );
	std::string sData = vsCookies.at( iCookie ).substr( splitPos + 1, std::string::npos );
	// check for empty data / whitespace data
	if ( sData == "" || sData.find_first_not_of(' ') != std::string::npos ){
	    continue;
	}
	m_mssData[ sKey ] = sData;
    }
}

/* virtual */ CookieParser::~CookieParser(){
    
}

/* virtual */ void CookieParser::Print( std::ostream & aStream /* = std::cout */ ){
    for ( auto it=m_mssData.begin(); it!=m_mssData.end(); ++it ){
	aStream << "\"" << it->first << "\" -> \"" << it->second << "\"" << std::endl;
    }
}

/* virtual */ std::vector<std::string> CookieParser::GetOperations(){
    std::vector<std::string> toBeReturned;
    toBeReturned.resize( lexical_cast<int>( GetData( "NumEntries" ) ) ); 
    for ( auto it=m_mssData.begin(); it!=m_mssData.end(); ++it ){
	if ( it->first.substr( 0, 2 ) == "Op" ){
	    toBeReturned.at( lexical_cast<int>( it->first.substr( 2, 1 ) ) ) = it->second;
	}
    }
    return toBeReturned;
}
