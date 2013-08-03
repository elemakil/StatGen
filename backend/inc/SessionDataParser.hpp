#ifndef SESSIONDATAPARSER_H
#define SESSIONDATAPARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "Utils.hpp"
#include "DataExchange.hpp"

class SessionDataParser {
public:
    SessionDataParser( std::string sFileName );
    virtual ~SessionDataParser();
    
    virtual inline unsigned int GetNumEntries() const { return m_uiNumEntries; }
    virtual std::vector<std::string> GetEntries();
    virtual void AddEntry( std::string sEntry );
    virtual void WriteData();
private:
    DataExchange m_Data;
    std::string m_sFileName;
    
    unsigned int m_uiNumEntries;
};


#endif // SESSIONDATAPARSER_H
