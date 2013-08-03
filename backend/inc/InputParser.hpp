#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <vector>
#include <algorithm>

class InputParser {
public:
    InputParser( std::string sInput );
    virtual ~InputParser();
private:
    // do syntax checks
    virtual bool m_fCheckSyntax();
    
    // store the input string
    std::string m_sInput;
};


#endif // INPUTPARSER_H
