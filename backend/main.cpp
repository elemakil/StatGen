#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Config.hpp"
#include "Particle.hpp"
#include "Ket.hpp"

// maximum number of characters to read in one cycle
const unsigned int uiMaxChar = 1;
char readBuffer[uiMaxChar+1]; // Store Data


void copyFiles(std::ifstream &in, std::ofstream &out)
{
  readBuffer[uiMaxChar] = 0;
	while (in) {
		in.read(readBuffer, uiMaxChar);
		//readBuffer[len] = 0;
		std::cout << readBuffer << std::flush;	// Write that shit now!
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
	oFile.open(config.Get<std::string>("LiveFileName").c_str());
	
	std::ifstream tFile;
	
	tFile.open(config.Get<std::string>("Template_Header").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	char *query_cstr = getenv("QUERY_STRING");
	if (!query_cstr)
		query_cstr = (char*)"ket=|uud>";

	//std::cout << query_cstr << std::flush;
	
	std::string query(query_cstr);
	std::string ket = query.substr(4);
	
	Ket k;
	vector<CompoundParticle *> *cpvec  = k.createCompounds(ket);
	if (cpvec)
	{		
		for (auto it = cpvec->begin(); it != cpvec->end(); it++)
		{
			cout << "\n";
			(*it)->Print();
		}
	}
	else
	{
		std::cout << "NO PARTICLES FOUND" << std::flush;
	}
	
	//	std::ifstream tFile2;
	//	std::cout << config.Get<std::string>("Template_Middle").c_str() << std::flush;
	//	tFile2.open("html/templates/middle.hts");
	tFile.open(config.Get<string>("Template_Middle").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	tFile.open(config.Get<string>("Template_Middle2").c_str());
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
