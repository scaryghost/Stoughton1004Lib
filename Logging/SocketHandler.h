#ifndef STOUGHTON1004LIB_SOCKETHANDLER_H
#define STOUGHTON1004LIB_SOCKETHANDLER_H

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include "Stoughton1004Lib/Logging/Handler.h"
#include "Stoughton1004Lib/Network/DatagramSocket.h"
#include "Stoughton1004Lib/Network/DatagramPacket.h"
#include "Stoughton1004Lib/Network/Socket.h"
#include <string>

namespace Stoughton1004Lib {

 /**
  * Sends messages to a remote server either via TCP or UDP
  * @author etsai
  */
class SocketHandler : public Handler {
public:
    /**
     * Operation mode of the handler
     */
    enum Mode {
        TCP,        ///< Use TCP to send the packets
        UDP         ///< Use UDP to send the packets
    };

    /**
     * Create a SocketHandler, sending the packets to given hostname and port, 
     * and using the specified mode
     * @param   hostname    Address of the remote machine to broadcast to
     * @param   port        Port of the remote machine
     * @param   mode        Operation mode, defaults to TCP
     * @throw   S1104LibException   If socket created failed, or could not establish 
     *                              a connection to the remote server (TCP mode)
     */
    SocketHandler(const std::string hostname, int port, Mode mode= TCP) throw(S1004LibException);
    /**
     * Closes the socket, if in TCP mode, and deallocate memory
     */
    ~SocketHandler();

    virtual bool publish(const std::string &msg);
    virtual void close();

private:
    Socket *tcpSocket;              ///< Handler's TCP socket
    DatagramSocket *udpSocket;      ///< Handler's UDP socket
    DatagramPacket *packet;         ///< Datagram packet storing the message to broadcast
};  //class SocketHandler

}   //namespace Stoughton1004Lib


#endif
