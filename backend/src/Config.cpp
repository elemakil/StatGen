#include "Config.hpp"

// Global static pointer used to ensure a single instance of the class.
/* static */ Config * Config::m_pInstance = 0;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/

Config * Config::GetInstance() {
    if ( ! m_pInstance )   // Only allow one instance of class to be generated.
        m_pInstance = new Config;
    return m_pInstance;
}


void Config::ReadDataFromFile( std::string sConfigFile ){
    DataExchange configReader;
    configReader.SetFile( sConfigFile.c_str() );
    configReader.ReadFromFile();
    SetTemplateFileName( configReader.Get<std::string>( "TemplateFileName" ) );
    SetLiveFileName( configReader.Get<std::string>( "LiveFileName" ) );
}
