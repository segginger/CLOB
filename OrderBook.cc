#include <iostream>
#include <string>
#include "ClobImpl.hh"

int main( int    argc, 
          char** argv )
{
  cout << "Welcome to the Central Limit Order Book" << endl;
  
  // TODO: help?
  // TODO: threading
  // TODO: enums?
  
  ClobImpl* impl = new ClobImpl(); // the one doing the work
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
