/*
   TCPAcceptor.h
   TCPAcceptor class interface. TCPAcceptor provides methods to passively
   establish TCP/IP connections with clients.
*/

#ifndef __tcpacceptor_h__
#define __tcpacceptor_h__

#include <string>
#include <netinet/in.h>
#include "tcpstream.h"

using namespace std;

class TCPAcceptor
{
    int    m_lsd;
    int    m_port;
    char   m_address[256];
    bool   m_listening;
    
  public:
    TCPAcceptor(int port, const char* address="");
    ~TCPAcceptor();

    int        start();
    TCPStream* accept();

  private:
    TCPAcceptor() {}
};

#endif