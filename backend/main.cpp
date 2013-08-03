#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Config.hpp"
#include "Particle.hpp

// maximum number of characters to read in one cycle
const unsigned int uiMaxChar = 1024;

void copyFiles(std::ifstream &in, std::ofstream &out)
{
	while (in) {
		char *readBuffer = new char[uiMaxChar]; // Store Data
		in.read(readBuffer, uiMaxChar);
		out << readBuffer << std::flush;	// Write that shit now!
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
	
	
	std::cout << getenv("QUERY_STRING") << std::flush;
	std::string query(getenv("QUERY_STRING"));
	std::string ket = query.substr(4);
	
	vector<CompoundParticle *> *cpvec  = k.createCompounds(ket);
	if (!cpvec)
		return -1;
	
	for (auto elem : *cpvec)
	{
		cout << "\n";
		elem->Print();
	}
	
	
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
