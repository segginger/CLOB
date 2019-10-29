#include <iostream>
#include <string>
#include "ClobImpl.hh"

namespace
{
  const double tickSize = 0.05; // fix on an exchange where this app runs on
}

int main( int    argc, 
          char** argv )
{
  cout << "Welcome to the Central Limit Order Book" << endl;
  
  ClobImpl* impl = new ClobImpl( tickSize ); // the one doing the work
  int ret = 3; // assume something went wrong, if all goes well, it will correct
  try
  {
    ret = impl->parseInput();
  }
  catch ( const exception& ex )
  {
    cerr << "ERR: caught exception in OderBook " << ex.what() << endl;
  }
  catch ( ... )
  {
    cerr << "ERR: caught generic exception in OderBook" << endl;
  }
  delete impl;
  return ret;
}
