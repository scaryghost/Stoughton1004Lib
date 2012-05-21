#ifndef STOUGHTON1004LIB_DATAGRAMSOCKET_H
#define STOUGHTON1004LIB_DATAGRAMSOCKET_H

#include <string>

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
    DatagramSocket(int port);

    void bind(int port);
    void receive(const DatagramPacket& packet);
    void send(const DatagramPacket& packet);

    int getLocalPort() const;
    int getPort() const;

private:
    int port;
};  //class DatagramSocket

}   //Stoughton1004Lib

#endif  //STOUGHTON1004LIB_DATAGRAMSOCKET_H
