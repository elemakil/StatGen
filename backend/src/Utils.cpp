
#include "Utils.hpp"

template <> std::string lexical_cast<std::string, std::string>( const std::string & from ){
    return from;
}

template <> std::string ToString<std::string>( const std::string & input ){
    return input;
}
