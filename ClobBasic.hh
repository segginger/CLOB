#ifndef CLOB_BASIC
#define CLOB_BASIC

#include <string>
using namespace std;

enum State
{
  OPEN             = 0, 
  PARTIALLY_FILLED = 1,
  FULLY_FILLED     = 2,
  CANCELLED        = 3
};

namespace
{
  string OPEN_STR             = "open";
  string PARTIALLY_FILLED_STR = "partially filled";
  string FULLY_FILLED_STR     = "fully filled";
  string CANCELLED_STR        = "cancelled";
  string ERR_STR              = "ERR";
}

class ClobState
{
  private:
    State m_state;
    
  public:
    ClobState(State state)
    {
      m_state = state;
    }
    
    virtual ~ClobState() {};
    
    bool operator==( const ClobState& a )
    {
      return m_state == a.m_state;
    }
    
    string getStr()
    {
      switch ( m_state )
      {
        case OPEN:             return OPEN_STR;
	case PARTIALLY_FILLED: return PARTIALLY_FILLED_STR;
	case FULLY_FILLED:     return FULLY_FILLED_STR;
	case CANCELLED:        return CANCELLED_STR;
	default:               return ERR_STR;
      }
    }
    
  private:
    ClobState();                                // not defined
    ClobState& operator=( const ClobState& a ); // not defined
};

#endif // CLOB_BASIC
