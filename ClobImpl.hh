#ifndef CLOB_IMPL
#define CLOB_IMPL

#include <string>

class ClobImpl
{
  public:
    ClobImpl() {};
    
    virtual ~ClobImpl() {};
    
  private:
    ClobImpl& operator=( const ClobImpl& a ); // not defined
    bool operator==( const ClobImpl& a );     // not defined
};

#endif // CLOB_IMPL
