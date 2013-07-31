#ifndef DATAEXCHANGE_H
#define DATAEXCHANGE_H

// include c/c++ stuff
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <map>

// my own stuff
#include "Utils.hpp"

using namespace std;

// Exception Class

class DataExchangeException : public std::exception {
public:
    DataExchangeException() : m_what( "Unknown Exception!" ){}
    DataExchangeException( std::string cause ) : m_what( cause ){}
    virtual ~DataExchangeException() throw() {}
    virtual const char * what() const throw();
private:
    std::string m_what;
};

// class that is used to write and read complex data to and from
// ordinary plain text files
class DataExchange {
public:
    DataExchange(){
        // default values
        m_bHasFileName = false;
    }
    ~DataExchange();

    // this is used to set the DataExchange file
    void SetFile( std::string name, bool readOnly = true ){ m_sFileName = name; m_bHasFileName = true; m_bReadOnly = readOnly; }

    // this is used to read data from a DataExchange file
    // and store it to one respectively
    void ReadFromFile();
    void WriteToFile();

    /*
     * Get the value from key and cast to type T
     * If key has multiple values, use the first or the one
     * specified by the second argument
     */
    template <typename T> T Get( std::string key, int entry = 0 ) const {
        T toReturn;
        // check whether key exists
        if ( m_Exists( key ) ){
            // check whether entry number specified is available
            if ( entry =! 0 && m_mDataStorage[ key ].size() <= entry ){
                DataExchangeException excp( std::string( "Value entry " ) + ToString( entry ) + std::string( "not found for parameter '" ) + key + std::string( "' in " ) + std::string( m_sFileName ) + std::string(".") );
                throw excp;
            }
            // use stringstreams for casting
            std::stringstream ss;
            ss << m_mDataStorage[ key ][ entry ];
            ss >> toReturn;
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
        return toReturn;
    }

    /*
     * Get value from key as std::vector<T>
     */
    template <typename T> std::vector<T> Get_Vector( std::string key ) const {
        std::vector<T> toReturn;
        // check whether key exists
        if ( m_Exists( key ) ){
            // loop entries
            for ( std::vector<std::string>::const_iterator it=m_mDataStorage[ key ].begin(); it!=m_mDataStorage[ key ].end(); ++it ) {
                // use stringstream for casting
                std::stringstream ss;
                T singleEntry;
                ss << (*it);
                ss >> singleEntry;
                toReturn.push_back( singleEntry );
            }
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
        return toReturn;
    }
    
        /*
     * Get value from key as std::list<T>
     */
    template <typename T> std::list<T> Get_List( std::string key ) const {
        std::list<T> toReturn;
        // check whether key exists
        if ( m_Exists( key ) ){
            // loop entries
            for ( std::vector<std::string>::const_iterator it=m_mDataStorage[ key ].begin(); it!=m_mDataStorage[ key ].end(); ++it ) {
                // use stringstream for casting
                std::stringstream ss;
                T singleEntry;
                ss << (*it);
                ss >> singleEntry;
                toReturn.push_back( singleEntry );
            }
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
        return toReturn;
    }

    /*
     * Get value from key as std::pair<T,U>
     * if key has not exactly two entries an exception is raised
     */
    template <typename T, typename U> std::pair<T,U> Get_Pair( std::string key ) const {
        std::pair<T,U> toReturn;
        // check whether key exists
        if ( m_Exists( key ) ){
            if ( m_mDataStorage[ key ].size() != 2 ){
                DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' from input '" ) + std::string( m_sFileName ) + std::string( "' has " ) + ToString( m_mDataStorage[ key ].size() ) + std::string( " entries and can not be casted to a pair.") );
                throw excp;
            }
            else {
                // use make_pair for casting
                toReturn = make_pair( m_mDataStorage[ key ][ 0 ], m_mDataStorage[ key ][ 1 ] )          ;
            }
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
        return toReturn;
    }

    /*
     * Add key with value to data collection
     */
    template <typename T> void Add( std::string key, T value ){
	if ( m_bReadOnly ){
	    DataExchangeException excp( std::string( "This instance of DataExchange is ReadOnly!" ) );
            throw excp;
	}
        if ( m_Exists( key ) ){
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' already present in data.") );
            throw excp;
        }
        else {
            // use stringstream for casting
            std::stringstream ss;
            std::string toAdd;
            ss << value;
            ss >> toAdd;
            m_mDataStorage[ key ].push_back( toAdd );
        }
    }

    /*
     * Add key with vector of values
     */
    template <typename T> void Add( std::string key, std::vector<T> values ){
	if ( m_bReadOnly ){
	    DataExchangeException excp( std::string( "This instance of DataExchange is ReadOnly!" ) );
            throw excp;
	}
	
        if ( m_Exists( key ) ){
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' already present in data.") );
            throw excp;
        }
        else {
            for ( size_t iVec=0; iVec<values.size(); iVec++ ){
                // use stringstream for casting
                std::stringstream ss;
                std::string toAdd;
                ss << values.at( iVec );
                ss >> toAdd;
                m_mDataStorage[ key ].push_back( toAdd );
            }
        }
    }

    /*
     * Delete value from key
     */
    void DeleteEntry( std::string key, unsigned int uiVec ){
	if ( m_bReadOnly ){
	    DataExchangeException excp( std::string( "This instance of DataExchange is ReadOnly!" ) );
            throw excp;
	}

        if ( m_Exists( key ) ){
            if ( m_mDataStorage[ key ].size() <= uiVec ){
                DataExchangeException excp( std::string( "Value entry " ) + ToString( uiVec ) + std::string( "not found for parameter '" ) + key + std::string( "' in " ) + std::string( m_sFileName ) + std::string(".") );
                throw excp;
            }
            else {
                m_mDataStorage[ key ].erase( m_mDataStorage[ key ].begin() + uiVec );
            }
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
    }

    /*
     * Delete key
     */
    void DeleteKey( std::string key ){
	if ( m_bReadOnly ){
	    DataExchangeException excp( std::string( "This instance of DataExchange is ReadOnly!" ) );
            throw excp;
	}

        if ( m_Exists( key ) ){
            m_mDataStorage.erase( key );
        }
        else {
            DataExchangeException excp( std::string( "Parameter '" ) + key + std::string( "' does not exist in " ) + std::string( m_sFileName ) + std::string(".") );
            throw excp;
        }
    }

    /*
     * Print the whole data set to std::cout
     */
    void PrintData();

    // clears the data container
    void Clear(){ 
	if ( m_bReadOnly ){
	    DataExchangeException excp( std::string( "This instance of DataExchange is ReadOnly!" ) );
            throw excp;
	}
	m_mDataStorage.clear(); 
    }
private:
    // ========== private member functions ========== //
    /*
     * Check whether the map is empty, i.e. no data is added
     */
    bool m_IsEmpty(){ return m_mDataStorage.empty(); }
    /*
     * Check whether an entry to a certain key exists
     */
    bool m_Exists( std::string key ) const {
        return m_mDataStorage.find( key ) != m_mDataStorage.end();
    }

    // class meta data
    std::string m_sFileName;
    bool m_bHasFileName;
    bool m_bReadOnly;

    // storage of all entries found in file or added to instance
    mutable std::map<std::string, std::vector<std::string> > m_mDataStorage;
};
#endif // end of DATAEXCHANGE_H
