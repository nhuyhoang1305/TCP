#include "common.h"
#include "packet.h"
#include <iostream>

Packet::Packet(){}
Packet::Packet( std::string header,
                std::string body)
    : header(header), body(body){}

std::string Packet::getHeader() { return this->header; }
unsigned int Packet::getHeaderSize() { return sizeof(this->header); }
std::string Packet::getBody() { return this->body; }
unsigned int Packet::getBodySize() {return sizeof(this->body); }
unsigned int Packet::getPacketSize() {return getHeaderSize() + getBodySize(); }

void Packet::setHeader(std::string header)
{
    this->header = header;
}
void Packet::setBody(std::string body)
{
    this->body = body;
}

ssize_t Packet::recv(TCPStream *stream)
{
    ssize_t ret;
    char buffer[BUFFER_SIZE];
    ret = stream->receive(buffer, sizeof(buffer));
    buffer[ret] = '\0';
    this->header = "";
    this->header.append(buffer);
    if (ret < 0)
    {
        perror("Header read error");
        return ret;
    }

    //unsigned int readSize = getLength() - getHeaderSize();
    unsigned int readSize = 1;
    if (readSize > 0)
    {
        buffer[0] = '0';
        ret = stream->receive(buffer, sizeof(buffer));
        buffer[ret] = '\0';
        if (ret < 0)
        {
            perror("Body read error");
            return ret;
        }
        this->body.append(buffer);
    }
    return ret;
}

ssize_t Packet::send (TCPStream *stream)
{
    // send header
    ssize_t ret;
    ret = stream->send(getHeader().c_str(), getHeaderSize());
    if (ret < 0)
    {
        std::cout << "Can't send header!["
        << stream->getPeerIP() << ":"
        << stream->getPeerPort() << "]\n";
        return ret;
    }
    // send body
    ret = stream->send(getBody().c_str(), getBodySize());

    if (ret < 0)
    {
        std::cout << "Can't send body!["
        << stream->getPeerIP() << ":"
        << stream->getPeerPort() << "]\n";
        return ret;
    }

    //reset body
    setBody("");
    return ret;
}