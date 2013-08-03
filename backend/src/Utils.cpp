
#include "Utils.hpp"

template <> std::string lexical_cast<std::string, std::string>( const std::string & from ){
    return from;
}

template <> std::string ToString<std::string>( const std::string & input ){
    return input;
}

void ReplaceAll( std::string & target, const std::string & from, const std::string & to ) {
    if ( from.empty() ){
        return;
    }
    size_t start_pos = 0;
    while ( ( start_pos = target.find( from, start_pos ) ) != std::string::npos ) {
        target.replace( start_pos, from.length(), to );
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
