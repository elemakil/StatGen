
#include "Utils.hpp"

template <std::string, std::string> std::string lexical_cast( const std::string & from ){
    return from;
}

template <std::string> std::string ToString( const std::string & input ){
    return input;
}
