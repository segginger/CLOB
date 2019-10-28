#include "ClobImpl.hh"
#include "ClobParser.hh"

ClobImpl::ClobImpl()
{
  m_parser = new ClobParser( this );
}

ClobImpl::~ClobImpl()
{
  delete m_parser;
  m_parser = NULL;
};

int ClobImpl::parseInput()
{
  return m_parser->parse();
}
