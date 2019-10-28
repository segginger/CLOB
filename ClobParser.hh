#ifndef CLOB_PARSER
#define CLOB_PARSER

#include <string>

class ClobParser
{
  public:
    ClobParser() {};
    
    virtual ~ClobParser() {};
    
  private:
    ClobParser& operator=( const ClobParser& a ); // not defined
    bool operator==( const ClobParser& a );       // not defined
};

#endif //CLOB_PARSER
