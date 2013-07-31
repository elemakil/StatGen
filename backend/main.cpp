#include <fstream>
#include <iostream>
#include <string>

#include "Config.hpp"

// maximum number of characters to read in one cycle
const unsigned int uiMaxChar = 1024;

int main( int argc, char * argv [] ) {
    
    // Setup the config
    Config::GetInstance()->SetTemplateFileName( "test.txt" );
    Config::GetInstance()->SetLiveFileName( "test2.txt" );
    
    std::ifstream tFile;
    tFile.open( Config::GetInstance()->GetTemplateFileName().c_str() );
    std::ofstream oFile;
    oFile.open( Config::GetInstance()->GetLiveFileName().c_str() );

    while ( tFile ){
    
    	char * readBuffer = new char[ uiMaxChar ];
    	tFile.read( readBuffer, uiMaxChar );

	oFile << readBuffer;
    }
    
    tFile.close();
    oFile.close();
	
    return 0;
}
