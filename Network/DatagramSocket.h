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
    DatagramSocket(std::string address, int port);

    void bind(int port);
    void receive(const DatagramPacket& packet);
    void send(const DatagramPacket& packet);

    int getLocalPort() const;
    int getPort() const;
    std::string getAddress() const;

private:
    std::string address;
    int port;
};

}   //Stoughton1004Lib

#endif  //STOUGHTON1004LIB_DATAGRAMSOCKET_H
