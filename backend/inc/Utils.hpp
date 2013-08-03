#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <vector>

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
 * @brief Replace all occurances from "match" by "replacement" in "target"
 * @param target the target std::string
 * @param match the original string
 * @param replacement the string to be used in the replacement
 */
void ReplaceAll( std::string & target, const std::string & match, const std::string & replacement );

/*!
 * @brief Replace first occurance of "match" by "replacement" in std::string "target"
 * @param target the target std::string
 * @param match the original string
 * @param replacement the string to be used in the replacement
 */
void Replace( std::string & target, const std::string & match, const std::string & replacement );


/*!
 * @brief splits a std::string into atoms separated by a delimiter
 * @param sInput the input std::string
 * @param cDelim the delimiter character
 * @param vsElements the std::vector of atomised items
 * The tokenised items are appended to the vsElements vector
 */
void Split( const std::string & sInput, char cDelim, std::vector<std::string> & vsElements);

/*!
 * @brief splits a std::string into atoms separated by a delimiter
 * @param sInput the input std::string
 * @param cDelim the delimiter character
 * @return a std::vector of the tokenised atoms
 */
std::vector<std::string> Split( const std::string & sInput, char cDelim );

#endif // UTILS_H
