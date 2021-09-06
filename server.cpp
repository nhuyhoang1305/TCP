/*
   server.cpp
   Test server for the tcpsockets classes which handles connections
   iteratively.
*/

#include <stdio.h>
#include <stdlib.h>
#include "tcpacceptor.h"
#include <cstring>
#include "common.h"
#include "packet.h"
#include <iostream>

int main(int argc, char** argv)
{
    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
    acceptor = new TCPAcceptor(SERVER_PORT, SERVER_IP);
    printf("Waiting client connection...\n");
    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream) {
                Packet packet;
                packet.setHeader("Elcom");
                //std::cout << "A client connected!" << stream->getPeerIP() << std::endl;

                while (packet.recv(stream) >= 0) {
                    if (packet.getBody() == "Quit")
                    {
                        delete stream;
                        break;
                    }
                    else
                    {
                        printf("received - %s\n", packet.getBody().c_str());
                        packet.send(stream);
                    }
                }
                //delete stream;
            }
        }
    }
    exit(0);
}
