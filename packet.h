#ifndef PACKET_H
#define PACKET_H

#include <string>
#include "tcpstream.h"

class Packet
{
private:
    // struct Header
    // {
    //     unsigned int cmd_length;
    //     unsigned int cmd_id;
    //     unsigned int cmd_status;
    //     unsigned int seq_number;
    // };
    // struct Body
    // {
    //     std::string username;
    //     std::string password;
    //     std::string system_id;
    //     std::string message;
    // };
    std::string header;
    std::string body;
public:
    Packet();
    Packet( std::string header,
            std::string body);
    // Packet( unsigned int length,
    //         unsigned int id,
    //         unsigned int status,
    //         unsigned int seq_number,
    //         std::string message );

    // unsigned int getLength        ();
    // unsigned int getId            ();
    // unsigned int getStatus        ();
    // unsigned int getSeqNumber     ();
    // unsigned int getHeaderSize    ();
    // unsigned int getMessageSize   ();
    // unsigned int getPacketSize    ();
    std::string getHeader();
    unsigned int getHeaderSize();
    std::string getBody();
    unsigned int getBodySize();
    unsigned int getPacketSize();
    void setHeader(std::string header);
    void setBody(std::string body);
    // void setLength  (unsigned int length);
    // void setId      (unsigned int id);
    // void setStatus  (unsigned int status);
    // void setSeqNumber  (unsigned int number);
    // void setMessage (std::string message);
    // void set (  unsigned int length,
    //             unsigned int id,
    //             unsigned int status,
    //             unsigned int number,
    //             std::string  message );

    ssize_t recv(TCPStream *stream);
    ssize_t send(TCPStream *stream);

    ssize_t processPackets(TCPStream *stream);
};

#endif