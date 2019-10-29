#include "ClobImpl.hh"
#include "ClobParser.hh"
#include "ClobBasic.hh"

namespace
{
  double MIN_DOUBLE = 1E-8; // numeric statbility and floating points
}

ClobImpl::ClobImpl( const double tickSize )
 : m_tickSize( tickSize )
 , m_parser( new ClobParser( this ) )
{}

ClobImpl::~ClobImpl()
{
  delete m_parser;
  m_parser = NULL;
};

int ClobImpl::parseInput()
{
  return m_parser->parse();
}

long ClobImpl::min( const long val1,
                    const long val2 )
{
  if ( val1 <= val1 )
  {
    return val1;
  }
  return val2;
}

void ClobImpl::insertOrder( long   id,
                	    bool   isBuy,
                	    long   quantity,
	        	    double price )
{
  cout << "insertOrder called for " << id << "|"
                                    << isBuy << "|"
                                    << quantity << "|"
				    << price << endl;
  
  long tickCheck = price / m_tickSize;
  double tickRemainder = price - (tickCheck*m_tickSize);
  if (tickRemainder > MIN_DOUBLE )
  {
    tickRemainder -= m_tickSize;
  }
  
  if ( abs(tickRemainder) > MIN_DOUBLE )
  {
    cout << "tick check: does not match for " << price 
         << " tickSize: " << m_tickSize << endl;
    return;
  }
  
  // matched the tick size, go on create the order:
  ClobOrder tmp( id, isBuy, quantity, price );
  
  // try to find a match:
  // a sell wants to find a buy
  // a buy wants to find a sell
  
  ClobOrdersIt it  = m_clobOrders.begin();
  ClobOrdersIt end = m_clobOrders.end();
  while ( it != end )
  {
    if ( it->getIsBuy() != isBuy )
    {
      // match found for buy/sell
      if ( ( isBuy  && price >= it->getPrice() ) ||
             !isBuy && price <= it->getPrice() )
      {
        cout << "match found: " << *it << endl;
	
	// can remove that matched amount for now:
	long quantReduce = min( tmp.getQuantity(), it->getQuantity() );
	
	it->setQuantity( it->getQuantity() - quantReduce );
	if ( it->getQuantity() == 0 )
	{
	  cout << "order fully matched with counterparty: move it to history" << endl;
	  it->setState( FULLY_FILLED );
	  m_histOrders.push_back( *it );
	  m_clobOrders.erase( it );
	}
	tmp.setQuantity( tmp.getQuantity() - quantReduce );
	if ( tmp.getQuantity() == 0 )
	{
	  cout << "input was put to the history" << endl;
	  tmp.setState( FULLY_FILLED );
	  m_histOrders.push_back( tmp );
	  return; // no more matching possible
	}
	tmp.setState( PARTIALLY_FILLED );
	cout << "fulfilled the match" << endl;
	// continue with the order
      }
    }
    ++it;
  }
  
  
  // move the remainder to the list
  m_clobOrders.push_back( tmp );
}

void ClobImpl::cancelOrder( long id )
{
  cout << "cancelOrder called for " << id << endl;
  ClobOrdersIt it  = m_clobOrders.begin();
  ClobOrdersIt end = m_clobOrders.end();
  while ( it != end )
  {
    if ( it->getId() == id )
    {
      if ( it->getState() == OPEN )
      {
	cout << "cancelOrder: found: " << *it << endl;
	it->setCancelled();
	break;
	m_histOrders.push_back( *it );
	m_clobOrders.erase( it );
	return;
      }
    }
    ++it;
  }
}

void ClobImpl::amendOrder( long id,
                           long newQuantity )
{
  cout << "amendOrder called for " << id << "|"
                                   << newQuantity << endl;
  ClobOrdersIt it  = m_clobOrders.begin();
  ClobOrdersIt end = m_clobOrders.end();
  while ( it != end )
  {
    cout << "amendOrder: found: " << *it << endl;
    if ( it->getId() == id )
    {
      if ( it->getQuantity() >= newQuantity )
      {
        it->setQuantity( newQuantity ); // amend down no penalty
      }
      else
      {
        it->setQuantity( newQuantity ); // amend up -> goes to end of list
	m_clobOrders.erase( it );
	m_clobOrders.push_back( *it );
	return;
      }
    }
    ++it;
  }
}

void ClobImpl::queryLevel( string bidAsk,
                           long   level )
{
  bool isBuy = BuySell::getIsBuyFromBidAsk( bidAsk );
  cout << "queryLevel called for " << bidAsk << "|"
                                   << isBuy << "|"
                                   << level << endl;
  ClobOrdersIt it  = m_clobOrders.begin();
  ClobOrdersIt end = m_clobOrders.end();
  size_t pos(0);
  while ( it != end )
  {
    if ( it->getIsBuy() == isBuy )
    {
      if ( pos == level )
      {
        printOrder( *it, pos );
	return;
      }
      ++pos;
    }
    ++it;
  }
}

void ClobImpl::printOrder(       ClobOrder& a,
                           const long       pos )
{
  cout << "Order information:" 
       << " id: " << a.getId()
       << " pos: " << pos
       << " b/s: " << a.getBuySell()
       << " remaining quantity: " << a.getQuantity()
       << " price: " << a.getPrice()
       << " status: " << ClobState::getStateStr( a.getState() )
       << endl;
}

void ClobImpl::queryOrder( long id )
{
  cout << "queryOrder called for " << id << endl;
  ClobOrdersIt it  = m_clobOrders.begin();
  ClobOrdersIt end = m_clobOrders.end();
  size_t pos(0);
  while ( it != end )
  {
    if ( it->getId() == id )
    {
      printOrder( *it, pos );
      return;
    }
    ++it;
    ++pos;
  }
  it  = m_histOrders.begin();
  end = m_histOrders.end();
  while ( it != end )
  {
    if ( it->getId() == id )
    {
      printOrder( *it, pos );
      return;
    }
    ++it;
    ++pos;
  }
}
