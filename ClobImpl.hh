#ifndef CLOB_IMPL
#define CLOB_IMPL

#include <string>
#include <iostream>

#include "ClobBasic.hh"

using namespace std;

class ClobParser; // forward declaration

class ClobImpl
{
  private:
    ClobParser* m_parser;
  
  public:
    ClobImpl();
    
    virtual ~ClobImpl();
    
    void insertOrder( long id,
                      bool isBuy,
                      long quantity,
	              double price )
    {
      cout << "insertOrder called for " << id << "|"
                                        << isBuy << "|"
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

    void queryLevel( string bidAsk,
                     long   level )
    {
      cout << "queryLevel called for " << bidAsk << "|"
                                       << level << endl;
    }

    void queryOrder( long id )
    {
      cout << "queryOrder called for " << id << endl;
    }

    int parseInput();
    
  private:
    ClobImpl& operator=( const ClobImpl& a ); // not defined
    bool operator==( const ClobImpl& a );     // not defined
};

#endif // CLOB_IMPL
