/*
   client.cpp
   Test client for the tcpsockets classes. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "tcpconnector.h"
#include <iostream>
#include "common.h"
#include "packet.h"

using namespace std;

int main(int argc, char** argv)
{
    int len;
    string message;
    char line[256];
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect(SERVER_IP, SERVER_PORT);
    
    if (stream)
    {
        cout << "Connected to server\n";
        Packet packet;
        while (true)
        {
            cout << "Input: ";
            getline(cin, message);
            packet.setHeader("ELCOM");
            packet.setBody(message);
            if (packet.getBody() == "Quit")
            {
                packet.send(stream);
                delete stream;
                break;
            }
            printf("sent - %s\n", packet.getBody().c_str());
            packet.send(stream);
            packet.recv(stream);
            printf("received - %s\n", packet.getBody().c_str());
        }
    }
    exit(0);
}