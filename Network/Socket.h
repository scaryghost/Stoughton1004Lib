#ifndef STOUGHTON1004LIB_SOCKET_H
#define STOUGHTON1004LIB_SOCKET_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"

#include <string>
#include <netinet/in.h>
#include <sys/socket.h>

namespace Stoughton1004Lib {

class ServerSocket;

class Socket {
public:
    /**
     * Create an unconnected socket
     */
    Socket() throw(S1004LibException);
    /**
     * Create a TCP socket, connected to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     */
    Socket(const std::string& hostname, int port) throw(S1004LibException);

    /**
     * Close the connection 
     */
    void close();
    /**
     * Connect to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     */
    void connect(const std::string& hostname, int port) throw(S1004LibException);
    /**
     * Write the message to the connection
     * @param   msg     Message to be written
     */
    void write(const std::string& msg) throw(S1004LibException);
    /**
     * Reads messages from the connection.  Reading stops when either 
     * there is nothing left or the number of bytes given has been read.  
     * If there is nothing to read when the function is called, it will 
     * hang until something is available to be read.
     * @param   nBytes  Number of bytes to read
     * @return  Message of at most nBytes length
     */
    std::string read(unsigned int nBytes) throw(S1004LibException);
    /**
     * Read characters from the connection until a newline (\n), 
     * return carriage (\r), or return carriage followed by new line (\r\n) 
     * is read.  The message will not contain the end of line characters.  If 
     * a newline or return carriage is not in the message, the function will 
     * hang until one is read.
     * @return  A line of characters from the connection
     */
    std::string readLine() throw(S1004LibException);

    /**
     * Returns the connected state of the socket
     * @return  True if the socket is connected
     */
    bool isConnected() const;

private:
    /**
     * Private constructor for building a Socket object when the 
     * file descriptor and address information are already known
     * @param   tcpSocket   File descriptor of the TCP socket
     * @param   addr        Address information about the connection
     */
    Socket(int tcpSocket, sockaddr_in *addr);
    /**
     * Initialize the member variables.  Need to do it this way because 
     * C++ doesn't support constructor delegation
     */    
    void init() throw(S1004LibException);

    bool closed;                    ///< Stores the closed state
    bool connected;                 ///< Store the connected state
    int tcpSocket;                  ///< Socket file descriptor
    sockaddr_in connectionInfo;     ///< Information about the connection

    friend class ServerSocket;
};  //class Socket

}   //namespace Stoughton1004Lib

#endif
