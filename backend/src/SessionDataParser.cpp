#include "SessionDataParser.hpp"

SessionDataParser::SessionDataParser( std::string sFileName ) : m_sFileName( sFileName ) {
    m_Data.SetFile( sFileName, false );
    m_Data.ReadFromFile();

    m_uiNumEntries = 0;
    
    // try to read the number of entries from the data file
    // if this fails, the file is newly created -> add the NumEntries field
    // and initialise to zero
    try {
	m_uiNumEntries = m_Data.Get<unsigned int>( "NumEntries" );
    }
    catch ( exception & e ) {
	m_uiNumEntries = 0;
	m_Data.Add( "NumEntries", m_uiNumEntries );
    }
}

/* virtual */ SessionDataParser::~SessionDataParser(){
    
}

/* virtual */ std::vector<std::string> SessionDataParser::GetEntries(){
    std::vector<std::string> toBeReturned;
    
    // try to read all the data from the file
    // if this fails, the file will be flushed
    // and an empty vector will be returned
    try {
	for ( size_t iEntry=0; iEntry<m_uiNumEntries; ++iEntry ){
	    std::string sThisKey = "Entry:" + ToString( iEntry );
	    std::vector<std::string> vsThisLine = m_Data.Get_Vector<std::string>( sThisKey );
	
	    std::ostringstream oss;
	    std::copy( vsThisLine.begin(), vsThisLine.end(), ostream_iterator<std::string>( oss ) );
	    toBeReturned.push_back( oss.str() );
	}
    }
    catch ( exception & e ) {
	m_Data.Clear();
	m_Data.WriteToFile();
	m_uiNumEntries = 0;
	toBeReturned.clear();
	return toBeReturned;
    }
    return toBeReturned;
}


/* virtual */ void SessionDataParser::AddEntry( std::string sEntry ){
    std::string sThisKey = "Entry:" + ToString( m_uiNumEntries++ );
    m_Data.Add( "NumEntries", m_uiNumEntries );
    m_Data.Add( sThisKey, sEntry );
}

/* virtual */ void SessionDataParser::WriteData(){
    m_Data.WriteToFile();    
}
