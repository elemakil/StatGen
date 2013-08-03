
#include "Utils.hpp"

template <> std::string lexical_cast<std::string, std::string>( const std::string & from ){
    return from;
}

template <> std::string ToString<std::string>( const std::string & input ){
    return input;
}

void ReplaceAll( std::string & target, const std::string & match, const std::string & replacement ) {
    if ( match.empty() ){
        return;
    }
    size_t startPos = 0;
    while ( ( startPos = target.find( match, startPos ) ) != std::string::npos ) {
        target.replace( startPos, match.length(), replacement );
        startPos += replacement.length();
    }
}


void Replace( std::string & target, const std::string & match, const std::string & replacement ) {
    size_t startPos = target.find( match );
    if ( startPos == std::string::npos ){
	return;
    }
    target.replace( startPos, match.length(), replacement );
    return;
}
