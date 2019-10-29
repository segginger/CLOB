#ifndef CLOB_PARSER
#define CLOB_PARSER

#include <string>
#include <iostream>
#include "ClobImpl.hh"

using namespace std;

namespace
{
  const string IN_TOKEN  = " ";
  const string IN_ORDER  = "order";
  const string IN_CANCEL = "cancel";
  const string IN_AMEND  = "amend";
  const string IN_QUERY  = "q";
  const string IN_LEVEL  = "level";
}

class ClobParser
{
  private:
    ClobImpl* m_impl;
  
  public:
    ClobParser( ClobImpl* impl )
    {
      m_impl = impl;
    };
    
    virtual ~ClobParser() {};
    
    string parseNextParam( const string& in, 
                                 size_t& startPos )
    {
      if ( in.length() >= startPos )
      {
        size_t end = in.find( IN_TOKEN, startPos+1 );
	if ( end == string::npos )
	{
	  end = in.length();
	}
	string nextToken = in.substr( startPos+1, end-startPos-1 );
        //cout << "parsed string token: |" << nextToken << "|" << endl;
	startPos = end; // update the caller
	return nextToken;
      }
      return "ERR in parsing";
    }
    
    long parseNextLong( const string  in, 
                              size_t& pos )
    {
      string a = parseNextParam( in, pos );
      return stol( a );
    }
    
    double parseNextDouble( const string  in, 
                                  size_t& pos )
    {
      string a = parseNextParam( in, pos );
      return stod( a );
    }
    
    int parse()
    { 
      string line;
      size_t pos( string::npos );
      while ( std::getline(cin, line) ) 
      {
	//cout << "Did read: " << line << endl;
	if ( line.length() == 0 )
	{
	  cerr << "ERR: No input was read, exiting" << endl;
	  return 1;
	}
	else
	{
	  pos = line.find( IN_TOKEN );
	  if ( pos != string::npos )
	  {
            string action = line.substr( 0, pos );
	    // TODO remove: cout << "Parsed: |" << action << "|" << endl; 

	    if ( action == IN_ORDER )
	    {
	      long id = parseNextLong( line, pos );
	      //cout << "did read id: " << id << endl;
	      string buySell = parseNextParam( line, pos );
	      //cout << "did read buySell: " << buySell << endl;;
	      bool isBuy = BuySell::getIsBuy( buySell );
	      long quantity = parseNextLong( line, pos );
	      double price = parseNextDouble( line, pos );
	      m_impl->insertOrder( id, isBuy, quantity, price );
	    }
	    else if ( action == IN_CANCEL )
	    {
	      long id = parseNextLong( line, pos );
	      m_impl->cancelOrder( id );
	    }
	    else if ( action == IN_AMEND )
	    {
	      long id = parseNextLong( line, pos );
	      long quantity = parseNextLong( line, pos );
	      m_impl->amendOrder( id, quantity );
	    }
	    else if ( action == IN_QUERY )
	    {
	      string levelOrder = parseNextParam( line, pos );
	      if ( levelOrder == IN_LEVEL )
	      {
	        string bidAsk = parseNextParam( line, pos );
		long level = parseNextLong( line, pos );
		m_impl->queryLevel( bidAsk, level );
	      }
	      else if ( levelOrder == IN_ORDER )
	      {
	        long id = parseNextLong( line, pos );
		m_impl->queryOrder( id );
	      }
	      else
	      {
	        cerr << "ERR: LevelOrder parsing error for " << levelOrder << endl;
		return 4;
	      }
	    }
	    else
	    {
	      cerr << "ERR: Could not parse input: " << line << endl;
	      return 2;
	    }
	  }
	}
      }
      return 0;
    }
    
  private:
    ClobParser();                                 // not defined
    ClobParser& operator=( const ClobParser& a ); // not defined
    bool operator==( const ClobParser& a );       // not defined
};

#endif //CLOB_PARSER
