#ifndef STOUGHTON1004LIB_DATAGRAMSOCKET_H
#define STOUGHTON1004LIB_DATAGRAMSOCKET_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/Network/DatagramPacket.h"

#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
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
    /**
     * Default constructor
     * @throw   S1004LibException   If an error occured during the socket creation
     */
    DatagramSocket() throw(S1004LibException);

    /**
     * Bind to first available random port between [30000,50000)
     * @throw   S1004LibException   If a port cannot be bound after 20 tries
     */
    void bind() throw(S1004LibException);
    /**
     * Bind to specific port
     * @param   port    Port number to bind to
     * @throw   S1004LibException   If the socket cannot be bound to the given port
     */
    void bind(int port) throw(S1004LibException);
    /**
     * Recieve a datagram packet.  The program will wait until a packet 
     * is received before continuing
     * @param   packet  The variable to store the received packet to
     * @throw   S1004LibException   If an error occured during the receiving
     */
    void receive(DatagramPacket& packet) throw(S1004LibException);
    /**
     * Send the datagram packet
     * @param   packet  The packet to send
     * @throw   S1004LibException   If an error occured during the sending
     */
    void send(const DatagramPacket& packet) throw(S1004LibException);

    /**
     * Get the port the socket is bound to on the local machine
     * @return  Local port the socket is bound to
     */
    int getLocalPort() const;

private:
    sockaddr_in socketInfo;     ///< Information about the socket
    int udpSocket;              ///< Socket file descriptor
};  //class DatagramSocket

}   //Stoughton1004Lib

#endif  //STOUGHTON1004LIB_DATAGRAMSOCKET_H
