#ifndef CLOB_ORDER
#define CLOB_ORDER

#include <iostream>
#include <string>
#include <list>
#include <set>

#include "ClobBasic.hh"

class ClobOrder
{
  private:
    long   m_id;
    bool   m_isBuy;
    long   m_quantity;
    double m_price;
    State  m_state;

  public:
    ClobOrder( const long   id,
               const bool   isBuy,
	       const long   quantity,
	       const double price )
      : m_id( id )
      , m_isBuy( isBuy )
      , m_quantity( quantity )
      , m_price( price )
      , m_state( OPEN )
    {
      cout << "order created with: " << id << "|"
                                     << isBuy << "|"
				     << quantity << "|"
				     << price << endl;
      
    }
    
    ClobOrder& operator=( const ClobOrder& a )
    {
      m_id       = a.m_id;
      m_isBuy    = a.m_isBuy;
      m_quantity = a.m_quantity;
      m_price    = a.m_price;
      m_state    = a.m_state;
    }
    
    friend ostream& operator<<(       ostream&   os, 
                                const ClobOrder& a )
    {
      return os << a.m_id << "|"
                << a.m_isBuy << "|"
		<< a.m_quantity << "|"
		<< a.m_price;
    }
    
    long getId()
    {
      return m_id;
    }
    
    State getState()
    {
      return m_state;
    }
    
    long getQuantity()
    {
      return m_quantity;
    }
    
    double getPrice()
    {
      return m_price;
    }
    
    bool getIsBuy()
    {
      return m_isBuy;
    }
    
    string getBuySell()
    {
      return BuySell::getBuySell( m_isBuy );
    }
    
    void setQuantity( const long quantity )
    {
      m_quantity = quantity;
    }
    
    void setCancelled()
    {
      m_state = CANCELLED;
    }    
    
    void setState( const State state )
    {
      m_state = state;
    }
    
  private:
    ClobOrder(); // not defined
};

typedef list< ClobOrder > ClobOrders;
typedef list< ClobOrder >::iterator ClobOrdersIt;
typedef set< double, ClobOrders > ClobPriceOrders;
typedef set< double, ClobOrders >::iterator ClobPriceOrdersIt;

#endif // CLOB_ORDER

