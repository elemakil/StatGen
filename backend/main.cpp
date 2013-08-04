#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Config.hpp"
#include "Particle.hpp"
#include "Ket.hpp"
#include "TemplateParser.hpp"
#include "CookieParser.hpp"
#include "Utils.hpp"

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
	
	char *cookie = getenv("HTTP_COOKIE");

	if (!cookie)
	  {
		cookie = "";
		//std::		cout << " resete ";
	  }
	//std::cout << cookie << std::endl;
	CookieParser cp(cookie);
	
	std::string setCookieString;

	
	
	char *query_cstr = getenv("QUERY_STRING");
	if (!query_cstr)
	{
		query_cstr = (char*)"ket=|uud>|123>";	
			//std::cout << "NOQUERY" << std::flush;
	}
	//std::cout << "TEST" << std::flush;

	//std::cout << query_cstr << std::flush;
	
	std::string query(query_cstr), ket;
	if (query.size() >= 7)
		ket = query.substr(4);
	else 
		ket = "|uud>|123>";
	
	int pos = ket.find('%');
	while (pos >= 0)
	{
		if (ket.length() > pos + 2)
		{
			char c1 = ket[pos+1];
			char c2 = ket[pos+2];
			if (c1 < 60)
				c1 -= 48;
			else
				c1 -= 55;
			if (c2 < 60)
				c2 -= 48;
			else
				c2 -= 55;
			char c = c1*0x10+c2;
			ket[pos] = c;
			ket.erase(pos+1, 2);
		}
		pos = ket.find('%');	
	}
	
	Ket k;
	vector<CompoundParticle *> *cpvec  = k.createCompounds(ket);
	
	
	
	
	
	int numentriesincookie = 0;
	if (cp.IsKeyPresent("NumEntries"))
		numentriesincookie = lexical_cast<int>(cp.GetData("NumEntries"));
	
	setCookieString += "Set-Cookie:NumEntries=" + ToString(numentriesincookie+1) + ";\n\r";
	setCookieString += "Set-Cookie:Op" + ToString(numentriesincookie) +  "=" + ket + ";\n\r";
	
	
	
	// setup the template file ifstream
	// and live file ofstream
	std::ofstream oFile;
	oFile.open(config.Get<std::string>("LiveFileName").c_str());
	std::ifstream tFile;
	
	/*tFile.open(config.Get<std::string>("Template_Header").c_str());
	copyFiles(tFile, oFile);
	tFile.close();*/
	
	std::cout << "Content-type: text/html\n\r";
	std::cout << setCookieString << "\n\r" << std::flush;
	
	string history;
	for (int i = 0; i < numentriesincookie; i++)
	{
		string b = cp.GetData("Op" + ToString(i));
		ReplaceAll(b, ">", "&gt;");
		history += b + "<br /><br />";
	}
	
	
	
	TemplateParser header(config.Get<std::string>("Template_Header"), config.Get<std::string>("LiveFileName"));
	header.AddData("___VAR_KET___", ket);
	header.AddData("___THEM_CONTENT___", history);
	header.PerformReplacement();
	
	if ( cpvec && ! cpvec->empty() ){
	    if ( cpvec->at( 0 )->GetNumConstituents() >= 2 && cpvec->at( 0 )->GetNumConstituents() <= 5 ){
		std::string sImageTemplateFile = config.Get<std::string>( "QuarkFilePrefix" ) + ToString( cpvec->at( 0 )->GetNumConstituents() ) + ".hts";
		TemplateParser image( sImageTemplateFile, config.Get<std::string>( "LiveFileName" ) );
		for ( size_t iPart=0; iPart<cpvec->at( 0 )->GetNumConstituents(); ++iPart ){
		    std::string sKey;
		    std::string sData;
		    
		    sKey = "___c" + ToString( iPart ) + "___";
		    sData = Colour::FileNames[ cpvec->at( 0 )->ReadConstituent( iPart ).Colour ];
		    image.AddData( sKey, sData );
		    
		    sKey = "___t" + ToString( iPart ) + "___";
		    sData = Flavour::Names[ cpvec->at( 0 )->ReadConstituent( iPart ).Flavour ];
		    if ( cpvec->at( 0 )->ReadConstituent( iPart ).Spin != Spin::NoSpin ){
			sData += Spin::Names[ cpvec->at( 0 )->ReadConstituent( iPart ).Spin ];
		    }
		    image.AddData( sKey, sData );
		}
		image.PerformReplacement();
	    }
	}
	
	
	//	std::ifstream tFile2;
	//	std::cout << config.Get<std::string>("Template_Middle").c_str() << std::flush;
	//	tFile2.open("html/templates/middle.hts");
	tFile.open(config.Get<string>("Template_Middle").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	if (cpvec)
	{		
		for (auto it = cpvec->begin(); it != cpvec->end(); it++)
		{
			cout << "\n";
			cout << "<b>";
			(*it)->HTMLPrint();
			cout << "</b><br /><br />";
		}
	}
	else
	{
		std::cout << "NO PARTICLES FOUND" << std::flush;
	}
	
	tFile.open(config.Get<string>("Template_Middle2").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	
	tFile.open(config.Get<string>("Template_Footer").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	// read infile, size of read portion is defined by uiMaxChar

	cp.Print();
	

	// dont foget to close that fstream file shit!
	oFile.close();
	return 0;
}
