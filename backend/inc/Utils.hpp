#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

// cast type U to type T
// using std::stringstream
template <typename T, typename U> T lexical_cast( const U & from ){
    std::stringstream ss;
    T out;

    ss << from;
    ss >> out;

    return out;
}

template <> std::string lexical_cast<std::string, std::string>( const std::string & from );

/*!
 * @brief Converts any input type to a std::string (assuming it can be converted)
 * @param input The (non-string) input
 * @tparam T the type of the input
 * @return input transformed to std::string
 *
 * This utilises a std::stringstream for casting
 */
template <typename T> std::string ToString( const T & input ) {
    std::stringstream ss;
    ss  <<  input;
    return ss.str();
}

template <> std::string ToString<std::string>( const std::string & input );


/*!
 * @brief Replace all occurances from "from" by "to" in "target"
 * @param target the target std::string
 * @param from the original match
 * @param to the replacement
 */
void ReplaceAll( std::string & target, const std::string & from, const std::string & to );

/*!
 * @brief Replace first occurance of "from" by "to" in std::string "target"
 * @param target the target std::string
 * @param from the original match
 * @param to the replacement
 */
void Replace( std::string & target, const std::string & from, const std::string & to );

#endif // UTILS_H
