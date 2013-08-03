#include <fstream>
#include <iostream>
#include <string>

#include "Config.hpp"

// maximum number of characters to read in one cycle
const unsigned int uiMaxChar = 1024;

void copyFiles(std::ifstream &in, std::ofstream &out)
{
	while (in) {
		char *readBuffer = new char[uiMaxChar]; // Store Data
		in.read(readBuffer, uiMaxChar);
		out << readBuffer;	// Write that shit!
	}
}

int main( int argc, char * argv [] ) {
	
	// Setup the config
	DataExchange config;
	config.SetFile("backend/config.cfg");
	config.ReadFromFile();
	//Config::GetInstance()->ReadDataFromFile( "config.cfg" );
	
	// setup the template file ifstream
	// and live file ofstream
	std::ofstream oFile;
	oFile.open(config.Get<string>("LiveFileName").c_str());
	
	std::ifstream tFile;
	
	tFile.open(config.Get<string>("Template_Header").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	tFile.open(config.Get<string>("Template_Middle").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	tFile.open(config.Get<string>("Template_Footer").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	// read infile, size of read portion is defined by uiMaxChar
	

	// dont foget to close that fstream file shit!
	oFile.close();
	return 0;
}
