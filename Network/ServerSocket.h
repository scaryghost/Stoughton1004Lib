#ifndef STOUGHTON1004LIB_SERVERSOCKET_H
#define STOUGHTON1004LIB_SERVERSOCKET_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"

#include <netinet/in.h>
#include <sys/socket.h>

namespace Stoughton1004Lib {

/**
 * Implements a server socket, waiting for TCP connections.  This class 
 * will manage the differences between WinSock and Linux socket types
 * @author etsai
 */
class ServerSocket {
public:
    /**
     * Creates an unbounded server socket
     */
    ServerSocket() throw(S1004LibException);
    /**
     * Creates a server socket bound to the specified port
     * @param   port    Port number to bind the server socket to
     */
    ServerSocket(int port) throw(S1004LibException);

    /**
     * Binds the server socket to the specified port
     * @param   port    Port number to bind the server socket to
     */
    void bind(int port) throw(S1004LibException);
    /**
     * Accepts an incoming connection to the server socket.  The function 
     * will hang until a connection is available
     * @return  Socket connecting to the client
     */
    Socket accept() throw(S1004LibException);
    /**
     * Closes the server socket
     */
    void close();

    /**
     * Returns binding state
     * @return  True if the server socket is already bound
     */
    bool isBound() const;
    /**
     * Returns closed state
     * @return  True if the server socket is closed
     */
    bool isClosed() const;

private:
    int tcpSocket;              ///< File descriptor for the socket
    bool isBound;               ///< Stores the bound state
    bool isConnected;           ///< Stores the closed state
    sockaddr_in serverInfo      ///< Information about the server socket;
};  //class ServerSocket

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_SERVERSOCKET_H
