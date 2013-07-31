#include "DataExchange.hpp"

const char * DataExchangeException::what() const throw() {
    static std::string retStr;
    retStr = std::string( "DataExchange Exception: ") + m_what;
    return retStr.c_str();
}

void DataExchange::ReadFromFile(){
    // Open Input File: check whether file name was given, open the file and check whether that worked
    if ( ! m_bHasFileName ){
        DataExchangeException excp( "No data file set!" );
        throw excp;
    }
    ifstream file( m_sFileName.c_str() );

    if ( file.fail() ) {
        DataExchangeException excp( std::string("Could not open ") + std::string( m_sFileName ) + std::string(".") );
        throw excp;
    }
    else {
        // successfully opened file!

        // the file is expected to be with a certain syntax:
        //      [space]name value <value ... value>[#comment]
        // where space is an optional whitespace, name is the
        // data fields name, value is the required data, value ... value
        // are additional data entries and #comment is an optional comment (initiated by )
        // the # sign

        // setup variables as required
        std::string sThisLine;  // stores current line
        int iLine;              // current line number
        typedef std::string::size_type size_string; // typedef makes is easier to write stuff

        // get lines one by one
        while ( getline( file, sThisLine ) ) {
            size_string iFirstChar = 0;
            size_string iLastChar = sThisLine.size();

            // take care of whitespace at start of line
            while ( iFirstChar != iLastChar && isspace( sThisLine[ iFirstChar ] ) ) {
                ++iFirstChar;
            }

            // create new iteration variable, position it after leading whitespace
            size_string iThisChar = iFirstChar;

            // check whether at end of line or at comment sign
            if ( iThisChar != iLastChar && sThisLine[ iThisChar ] != '#' ) {

                // get the key of the current line
                std::string thisKey;

                while ( iThisChar != iLastChar && ! isspace( sThisLine[ iThisChar ] ) ){
                    ++iThisChar;
                }
                if ( iFirstChar != iThisChar ){
                    thisKey = sThisLine.substr( iFirstChar, iThisChar - iFirstChar );
                }
                iFirstChar = iThisChar;

                // remove whitespace after the key
                while ( iFirstChar != iLastChar && isspace( sThisLine[ iFirstChar ] ) ){
                    ++iFirstChar;
                }

                // work on the rest
                if ( iFirstChar != iLastChar ) {
                    std::vector<std::string> v_thisValue;

                    // strings can be delimited by quotation marks
                    if ( sThisLine[ iFirstChar ] == '"' || sThisLine[ iFirstChar ] == '"' ) {

                        ++iFirstChar;
                        iThisChar = iFirstChar;

                        bool inQuotes = true;

                        std::string thisValue = "";

                        for ( ; iFirstChar!=iLastChar; ++iFirstChar ){

                            // are qe still in quotes?
                            if ( inQuotes ){

                                // are we again at a quotation mark? (-> end of string)
                                if ( sThisLine[ iFirstChar ] == '"' ) {
                                    inQuotes = false;
                                    v_thisValue.push_back( thisValue );
                                    thisValue = "";
                                }
                                else if ( sThisLine[ iFirstChar ] == '\\' ){ // we are at an escape character, take care of it!

                                    // string line was not terminated -> throw exception!
                                    if ( iFirstChar + 1 == iLastChar ){
                                        DataExchangeException excp( ( std::string( m_sFileName ) + std::string(" line ") + ToString( iLine ) + std::string(": Unexpected end of line.") ).c_str() );
                                        throw excp;
                                    }
                                    else {
                                        if ( sThisLine[ iFirstChar + 1 ] == '\\' ){
                                            thisValue += '\\';
                                            ++iFirstChar;
                                        }
                                        else if ( sThisLine[ iFirstChar + 1 ] == '"' ) {
                                            // there's an escaped quotation mark
                                            thisValue += sThisLine[ iFirstChar + 1 ];
                                            ++iFirstChar;
                                        }
                                        else {
                                            // nothing special -> add the escape character to value holder
                                            thisValue += '\\';
                                        }
                                    }
                                } // are we at an escape character?
                                else {
                                    // nothing special (no escape character etc...) -> add character/space to string
                                    thisValue += sThisLine[ iFirstChar ];
                                }
                            } // are we still in quotes?
                            else { // no longer in quotes!
                                if ( sThisLine[ iFirstChar ] == '#' ){ // comment -> abort parsing for this line
                                    break;
                                }
                                else if ( sThisLine[ iFirstChar ] == '"' ){
                                    // we are at the start of a new string
                                    inQuotes = true;
                                }
                                else if ( ! isspace( sThisLine[ iFirstChar] ) ) {
                                    // a syntax error occured!
                                    DataExchangeException excp( std::string( m_sFileName ) + std::string(" line ") + ToString( iLine ) + std::string(": Syntax error.") );
                                    throw excp;
                                }
                            }
                        } // for loop over linechars
                        if ( inQuotes ){ // in quotes but at end of line -> throw exception!
                            DataExchangeException excp( std::string( m_sFileName ) + std::string(" line ") + ToString( iLine ) + std::string(": Unexpected end of line.") );
                            throw excp;
                        }

                    } // is a string
                    else {      // is a non-string value (at least its not delimited by quotation marks)
                        while ( iFirstChar != iLastChar && sThisLine[ iFirstChar ] != '#' ){
                            // loop as long as line and no comment sign
                            iThisChar = iFirstChar;
                            // as long as we are not at the end of line, at a comment sign and there's no whitespace character move marker further right
                            // because unless any of the above are false we are still working on the same entry for the original key
                            while ( iFirstChar != iLastChar && sThisLine[ iFirstChar ] != '#' && ! isspace( sThisLine[ iFirstChar ] ) ){
                                ++iFirstChar;
                            }
                            if ( iFirstChar != iThisChar ){
                                v_thisValue.push_back( sThisLine.substr( iThisChar, iFirstChar - iThisChar ) );
                            }
                            while ( iFirstChar != iLastChar && isspace( sThisLine[ iFirstChar ] ) ){
                                ++iFirstChar;
                            }

                        }
                    }
                    m_mDataStorage[ thisKey ] = v_thisValue;
                }
                else {          // no value was specified for the key
                    DataExchangeException excp( std::string( m_sFileName ) + std::string(" line ") + ToString( iLine ) + std::string(": No value specified for '") + thisKey + std::string("'.") );
                    throw excp;
                }
            } // char iteration var is neither at end of line nor at comment sign
            ++iLine;
        } // while getline
    } // NOT file.fail()
} // ReadFromFile()

// empty destructor
DataExchange::~DataExchange(){}

// ========== template specialisation for strings ========== //
template <> std::string DataExchange::Get<std::string>( std::string key, int entry /* = 0 */ ) const {
    if ( m_Exists( key ) ){
        return m_mDataStorage[ key ][ 0 ];
    }
    else {
        DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
        throw excp;
    }
}

template <> std::vector<std::string> DataExchange::Get_Vector<std::string>( std::string key ) const {
    if ( m_Exists( key ) ){
        return m_mDataStorage[ key ];
    }
    else {
        DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
        throw excp;
    }
}

template <> void DataExchange::Add( std::string key, std::string value ){
    if ( m_Exists( key ) ){
        DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' already present in data.") );
        throw excp;
    }
    else {
        m_mDataStorage[ key ].push_back( value );
    }
}

template <> void DataExchange::Add( std::string key, std::vector<std::string> values ){
    if ( m_Exists( key ) ){
        DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' already present in data.") );
        throw excp;
    }
    else {
        m_mDataStorage[ key ] = values;
    }
}

// ========== Print Data To STD::COUT ========== //
void DataExchange::PrintData(){
    std::cout << "DataExchange Data:" << std::endl;
    for ( std::map<std::string,std::vector<std::string> >::iterator it=m_mDataStorage.begin(); it!=m_mDataStorage.end(); ++it ) {
        std::cout << "Key: "<< (*it).first << " Value: ";
        for ( int i=0, N=(*it).second.size(); i!=N; ++i ){
            std::cout << (*it).second[i] << " ";
        }
        std::cout << std::endl;
    }
}

// ========== Write Data To File ========== //
void DataExchange::WriteToFile(){
    // check whether data file was set
    if ( ! m_bHasFileName ){
        DataExchangeException excp( std::string( "No outfile name set!" ) );
        throw excp;
    }

    // check whether data is not empty
    if ( m_IsEmpty() ){
        DataExchangeException excp( std::string( "Data is Empty!" ) );
        throw excp;
    }
    // open file
    std::ofstream out( m_sFileName.c_str() );

    // check whether opening worked
    if ( ! out.is_open() ){
        DataExchangeException excp( std::string( "Error opening file '" ) + std::string( m_sFileName ) + std::string( "' for writing!" ) );
        throw excp;
    }

    // write data
    for ( std::map<std::string,std::vector<std::string> >::iterator it=m_mDataStorage.begin(); it!=m_mDataStorage.end(); ++it ) {
        out << (*it).first << " ";
        for ( int i=0, N=(*it).second.size(); i!=N; ++i ){
            out << (*it).second[i] << " ";
        }
        out << std::endl;
    }

    // close file
    out.close();
}
