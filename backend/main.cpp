#include <fstream>
#include <iostream>
#include <string>

#include "Config.hpp"

// maximum number of characters to read in one cycle
const unsigned int uiMaxChar = 1024;

int main( int argc, char * argv [] ) {
    
    // Setup the config
    Config::GetInstance()->ReadDataFromFile( "config.cfg" );
    
    // setup the template file ifstream
    // and live file ofstream
    std::ifstream tFile;
    tFile.open( Config::GetInstance()->GetTemplateFileName().c_str() );
    std::ofstream oFile;
    oFile.open( Config::GetInstance()->GetLiveFileName().c_str() );

    // read infile, size of read portion is defined by uiMaxChar
    while ( tFile ){
    	char * readBuffer = new char[ uiMaxChar ]; // Store Data
    	tFile.read( readBuffer, uiMaxChar );
	
	oFile << readBuffer;	// Write that shit!
    }

    // dont foget to close that fstream file shit!
    tFile.close();
    oFile.close();
	
    return 0;
}
