#ifndef COOKIEPARSER_H
#define COOKIEPARSER_H

#include <string>
#include <map>
#include <ostream>
#include <iostream>
#include <vector>

#include "Utils.hpp"

class CookieParser {
public:
    CookieParser( char * cookies );
    virtual ~CookieParser();
    
    virtual void Print( std::ostream & aStream = std::cout );
    
    virtual inline std::string GetData( std::string sKey ) { return m_mssData[ sKey ]; }
    virtual inline bool IsKeyPresent( std::string sKey ) { return ( m_mssData.find( sKey ) != m_mssData.end() ); }
    
    virtual std::vector<std::string> GetOperations();
private:
    std::map<std::string,std::string> m_mssData;
};


#endif // COOKIEPARSER_H
