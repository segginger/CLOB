#include <iostream>
#include <string>
#include "ClobBasic.hh"
#include "ClobParser.hh"

namespace
{
  const string IN_TOKEN  = " ";
  const string IN_ORDER  = "order";
  const string IN_CANCEL = "cancel";
  const string IN_AMEND  = "amend";
  const string IN_QUERY  = "q";
  const double TICK_SIZE = 0.5; // TODO
}

void insertOrder( long id, 
                  long quantity,
	          double price )
{
  cout << "insertOrder called for " << id << "|"
                                    << quantity << "|"
				    << price << endl;
}

void cancelOrder( long id )
{
  cout << "cancelOrder called for " << id << endl;
}

void amendOrder( long id,
                 long newQuantity )
{
  cout << "amendOrder called for " << id << "|"
                                   << newQuantity << endl;
}

void queryLevel( string action,
                 long   level )
{
  cout << "queryLevel called for " << action << "|"
                                   << level << endl;
}

void queryOrder( long id )
{
  cout << "queryOrder called for " << id << endl;
}

int parseInput()
{
  string line;
  size_t pos(string::npos);
  while ( std::getline(cin, line) ) 
  {
    cout << "Did read: " << line << endl;
    if ( line.length() == 0 )
    {
      cerr << "No input was read, exiting" << endl;
      return 1;
    }
    else
    {
      pos = line.find( IN_TOKEN );
      if ( pos != string::npos )
      {
        string action = line.substr(0,pos);
	// TODO remove: cout << "Parsed: |" << action << "|" << endl; 
	
	if ( action == IN_ORDER )
	{
	  queryOrder( 1 ); // TODO
	}
	else if ( action == IN_CANCEL )
	{
	  queryOrder( 1 ); // TODO
	}
	else if ( action == IN_AMEND )
	{
	  queryOrder( 1 ); // TODO
	}
	else if ( action == IN_QUERY )
	{
	  queryOrder( 1 ); // TODO
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

int main( int    argc, 
          char** argv )
{
  cout << "Welcome to the Central Limit Order Book" << endl;
  
  // TODO: help?
  // TODO: threading
  // TODO: enums?
  
  return parseInput();
}
