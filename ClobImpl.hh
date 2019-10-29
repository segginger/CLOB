#ifndef CLOB_IMPL
#define CLOB_IMPL

#include <string>
#include <iostream>

#include "ClobBasic.hh"
#include "ClobOrder.hh"

using namespace std;

class ClobParser; // forward declaration

class ClobImpl
{
  private:
    ClobParser*      m_parser;
    double           m_tickSize;
    ClobOrders       m_clobOrders; // active group
    ClobOrders       m_histOrders; // processed/cancelled group, for speed
                                   // as over time this will grow a lot
  
  public:
    ClobImpl( const double tickSize );
    
    virtual ~ClobImpl();
    
    void insertOrder( long   id,
                      bool   isBuy,
                      long   quantity,
                      double price );

    void cancelOrder( long id );

    void amendOrder( long id,
                     long newQuantity );

    void queryLevel( string bidAsk,
                     long   level );

    void queryOrder( long id );

    int parseInput();
    
  private:
    ClobImpl();                               // not defined
    ClobImpl& operator=( const ClobImpl& a ); // not defined
    bool operator==( const ClobImpl& a );     // not defined
};

#endif // CLOB_IMPL
