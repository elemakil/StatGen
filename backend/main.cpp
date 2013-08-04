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
	int numentriesincookie = 0;
	if (cp.IsKeyPresent("NumEntries"))
		numentriesincookie = lexical_cast<int>(cp.GetData("NumEntries"));
	
	std::string setCookieString;
	std::string DEEEEEBUG;

	
	
	char *query_cstr = getenv("QUERY_STRING");
	if (!query_cstr && !numentriesincookie)
	{
		query_cstr = (char*)"ket=|uud>|123>";	
			//std::cout << "NOQUERY" << std::flush;
	}
	
	//std::cout << "TEST" << std::flush;

	//std::cout << query_cstr << std::flush;
	
	std::string query(query_cstr), ket;
	
	if (numentriesincookie)
		ket = cp.GetData("Op" + ToString(numentriesincookie-1));
	
	if (query.substr(0,4) == "ket=" && query.size() >= 7)
		ket = query.substr(4);
	else if (!numentriesincookie)
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
	
	DEEEEEBUG += query;
	if (query.substr(0,7) == "action=" && numentriesincookie)
	{
		DEEEEEBUG += "1";
		if (query.substr(0,12) == "action=clear")
		{
			DEEEEEBUG += "2";
			for (int i = numentriesincookie - 1; i >= 0; i--)
			{
				setCookieString += "Set-Cookie: Op" + ToString(i) + "=del; Expires=Thu, 01 Jan 1970 00:00:01 GMT;\n\r";
				DEEEEEBUG += "2b";
			}
			numentriesincookie = 0;
			DEEEEEBUG += "3";
		}
		
		
		
		
		if (query.substr(0,13) == "action=parity" || query.substr(0,13) == "action=charge" || query.substr(0,11) == "action=time")
		{
			std::stringstream newket;
			for (auto it = cpvec->begin(); it != cpvec->end(); it++)
			{
				if (it != cpvec->begin())
					newket << "+";
							
				if (query.substr(0,13) == "action=parity")
					Operators::TransformP(**it);
				if (query.substr(0,13) == "action=charge")
					Operators::TransformC(**it);
				if (query.substr(0,11) == "action=time")
					Operators::TransformT(**it);
				(*it)->PrintShort(newket);
 			}
			ket = newket.str();
		}
	}
	
	
	
	
	
	
	

	if (query.substr(0,9) != "page=info")
	{
		setCookieString += "Set-Cookie:NumEntries=" + ToString(numentriesincookie+1) + ";\n\r";
		setCookieString += "Set-Cookie:Op" + ToString(numentriesincookie) +  "=" + ket + ";\n\r";
	}
	
	
	
	// setup the template file ifstream
	// and live file ofstream
	std::ofstream oFile;
	oFile.open(config.Get<std::string>("LiveFileName").c_str());
	std::ifstream tFile;
	
	/*tFile.open(config.Get<std::string>("Template_Header").c_str());
	copyFiles(tFile, oFile);
	tFile.close();*/
	
	
	
	string history;
	for (int i = numentriesincookie - 1; i >= max(0,numentriesincookie-30); i--)
	{
		string b = cp.GetData("Op" + ToString(i));
		string c = b;
		ReplaceAll(b, ">", "&gt;");
		history +="<a href=\"?ket=" + c + "\">" +  b + "</a><br /><br />";
		
		if (numentriesincookie > 30)
			setCookieString += "Set-Cookie: Op" + ToString(numentriesincookie-30) + "=del; Expires=Thu, 01 Jan 1970 00:00:01 GMT;\n\r";
	}
	
	std::cout << "Content-type: text/html\n\r";
	std::cout << setCookieString << "\n\r" << std::flush;
	
	TemplateParser header(config.Get<std::string>("Template_Header"), config.Get<std::string>("LiveFileName"));
	header.AddData("___VAR_KET___", ket);
	header.AddData("___THEM_CONTENT___", history);
	//header.AddData("___THEM_OVERAL_COLOR___", cpvec->at( 0 )->GetAbsoluteColor);
	
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
		    sData = "";
		    if ( static_cast<int>( cpvec->at( 0 )->ReadConstituent( iPart ).Flavour ) < 0 ){
			sData = std::string( "<span style=\"text-decoration: overline;\">" );
		    }
		    sData += Flavour::GetUName( cpvec->at( 0 )->ReadConstituent( iPart ).Flavour );
		    if ( static_cast<int>( cpvec->at( 0 )->ReadConstituent( iPart ).Flavour ) < 0 ){
			sData += std::string( "</span>" );
		    }
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
	
	if (query.substr(0,9) == "page=info")
	{
		tFile.open(config.Get<string>("Template_Info").c_str());
		copyFiles(tFile, oFile);
		tFile.close();
	}
	else if (cpvec)
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
	
/*	tFile.open(config.Get<string>("Template_Middle2").c_str());
	copyFiles(tFile, oFile);
	tFile.close();*/
	
	tFile.open(config.Get<string>("Template_Footer").c_str());
	copyFiles(tFile, oFile);
	tFile.close();
	/*TemplateParser footer(config.Get<std::string>("Template_Footer"), config.Get<std::string>("LiveFileName"));
	header.AddData("___SEARCH_ME___", "REPLACE ME");
	footer.PerformReplacement();*/
	// read infile, size of read portion is defined by uiMaxChar
/*
	cp.Print();
	std::cout << "<!-- cokies: " << setCookieString << "\n\r" << " --->" << std::flush;
	std::cout << "<!-- DEEEEEBUG: " << DEEEEEBUG << "\n\r" << " --->" << std::flush;*/

	// dont foget to close that fstream file shit!
	oFile.close();
	return 0;
}
