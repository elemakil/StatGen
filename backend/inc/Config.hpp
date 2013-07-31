#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "DataExchange.hpp"

// Config Class (storing config etc.)
// implemented using singleton design pattern
class Config {
public:
    // singleton
    static Config * GetInstance();

    virtual ~Config(){}
    
    const std::string & GetTemplateFileName() const { return m_sTemplateFileName; }
    const std::string & GetLiveFileName() const { return m_sLiveFileName; }
    
    void SetTemplateFileName( const std::string & sFileName ){ m_sTemplateFileName = sFileName; }
    void SetLiveFileName( const std::string & sFileName ){ m_sLiveFileName = sFileName; }
    
    void ReadDataFromFile( std::string sConfigFile );
    
private:
    // singleton
    Config(){};  // Private so that it can  not be called
    Config( Config const & );             // copy constructor is private
    Config & operator=( Config const & );  // assignment operator is private
    
    static Config * m_pInstance;
    
    // data
    std::string m_sTemplateFileName;
    std::string m_sLiveFileName; 
};

#endif // CONFIG_H
