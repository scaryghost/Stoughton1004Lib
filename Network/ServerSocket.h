#ifndef STOUGHTON1004LIB_SERVERSOCKET_H
#define STOUGHTON1004LIB_SERVERSOCKET_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/Network/Socket.h"

#ifdef WIN32
#include <WinSock2.h>

#pragma warning( disable : 4290 )
#else
#include <netinet/in.h>
#include <sys/socket.h>
#endif

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
     * Closes the socket
     */
    ~ServerSocket();

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
    /**
     * Initialize the member variables.  Need to do it this way 
     * beacuse C++ doesn't support constructor delegation
     */
    void init() throw(S1004LibException);

    int tcpSocket;              ///< File descriptor for the socket
    bool bound;                 ///< Stores the bound state
    bool closed;                ///< Stores the closed state
    sockaddr_in serverInfo;     ///< Information about the server socket;
};  //class ServerSocket

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_SERVERSOCKET_H
