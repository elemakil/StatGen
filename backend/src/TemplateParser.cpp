#include "TemplateParser.hpp"

#include "Utils.hpp"

TemplateParser::TemplateParser( std::string sInFileName /* = "" */, std::string sOutFileName /* = "" */ ){
    if ( sInFileName != "" ){
	m_sInFileName = sInFileName;
	m_bHasSetInFile = true;
    }
    else {
	m_bHasSetInFile = false;
    }
    
    if ( sOutFileName != "" ){
	m_sOutFileName = sOutFileName;
	m_bHasSetOutFile = true;
    }
    else {
	m_bHasSetOutFile = false;
    }
    
    m_bHasGivenData = false;
    m_sReplacementDelimiter = "$";
}


/* virtual */ TemplateParser::~TemplateParser(){
    
}

/* virtual */ void TemplateParser::AddData( std::string sKeyField, std::string sReplacement ){
    m_bHasGivenData = true;
    m_mssData[ sKeyField ] = sReplacement;
}

/* virtual */ void TemplateParser::PerformReplacement(){
    if ( ! m_bHasSetInFile ){
	std::cerr << "ERROR: Input File was not set!" << std::endl;
	return;
    }
    
    if ( ! m_bHasSetOutFile ){
	std::cerr << "ERROR: Output File was not set!" << std::endl;
	return;
    }
    
    if ( ! m_bHasGivenData ){
	std::cerr << "ERROR: No Data given!" << std::endl;
	return;
    }
    
    std::ifstream inFile;
    inFile.open( m_sInFileName.c_str() );
    
    if ( inFile.fail() ) {
	std::cerr << "Error Opening file \"" << m_sInFileName << "\" for reading!" << std::endl;
	return;
    }
    
    std::ofstream outFile;
    outFile.open( m_sOutFileName.c_str() );
    
    if ( outFile.fail() ) {
	std::cerr << "Error Opening file \"" << m_sOutFileName << "\" for writing!" << std::endl;
	return;
    }
    
    // We are good to go!
    std::string sThisLine;
    
    while ( getline( inFile, sThisLine ) ){
	for ( auto it=m_mssData.begin(); it!=m_mssData.end(); ++it ){
	    std::string searchFor = m_sReplacementDelimiter + it->first + m_sReplacementDelimiter;
	    ReplaceAll( sThisLine, searchFor, it->second );
	}
	outFile << sThisLine << std::endl;
    }
    
    inFile.close();
    outFile.close();
}
