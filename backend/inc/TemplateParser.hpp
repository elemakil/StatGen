#ifndef TEMPLATEPARSER_H
#define TEMPLATEPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class TemplateParser {
public:
    TemplateParser( std::string sInFileName = "", std::string sOutFileName = "" );
    virtual ~TemplateParser();
    
    virtual inline void SetInFile( std::string sInFile ){ m_sInFileName = sInFile; m_bHasSetInFile = true; }
    virtual inline void SetOutFile( std::string sOutFile ){ m_sOutFileName = sOutFile; m_bHasSetOutFile = true; }
    
    virtual void AddData( std::string sKeyField, std::string sReplacement );
    virtual inline void SetDelimiter( std::string sDelimiter ){ m_sReplacementDelimiter = sDelimiter; }
    
    virtual void PerformReplacement();
private:
    bool m_bHasSetInFile;
    bool m_bHasSetOutFile;
    bool m_bHasGivenData;
    
    std::string m_sInFileName;
    std::string m_sOutFileName;
    
    std::string m_sReplacementDelimiter;
    std::map<std::string,std::string> m_mssData;
};


#endif // TEMPLATEPARSER_H
