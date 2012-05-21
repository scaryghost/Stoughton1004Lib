#ifndef STOUGHTON1004LIB_DATAGRAMSOCKET_H
#define STOUGHTON1004LIB_DATAGRAMSOCKET_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"

#include <string>
#include <sys/types.h>

namespace Stoughton1004Lib {

/**
 * Wrapper for the C udp socket functions.
 * This class will deal with differences between 
 * winsock and Linux's socket types
 * @author etsai
 */
class DatagramSocket {
public:
    DatagramSocket();

    void bind() throw(S1004LibException);
    void bind(int port) throw(S1004LibException);
    void receive(DatagramPacket& packet) throw(S1004LibException);
    void send(const DatagramPacket& packet) throw(S1004LibException);

    int getLocalPort() const;

private:
    sockaddr_in socketInfo;
    int udpSocket;
};  //class DatagramSocket

}   //Stoughton1004Lib

#endif  //STOUGHTON1004LIB_DATAGRAMSOCKET_H
