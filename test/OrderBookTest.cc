#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include "../ClobImpl.hh"

namespace
{
  const double TICK_SIZE = 0.05;
}

BOOST_AUTO_TEST_CASE( OrderBookTest )
{
  ClobImpl* impl = new ClobImpl( TICK_SIZE ); // the one doing the work
  
  // seven ways to detect and report the same error:
  BOOST_CHECK( impl->min( 2,3 ) == 2 );
  
  impl->insertOrder( 1001, true, 100, 10.10 );
  
  BOOST_CHECK( impl->cancelOrder( 1001 ) == true );
  
  BOOST_CHECK( impl->cancelOrder( 1001 ) == false );
  
  // no more methods that have return values
  // unit test basics: done
  
  delete impl;
  impl = NULL;
}
