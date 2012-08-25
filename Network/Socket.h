#ifndef STOUGHTON1004LIB_SOCKET_H
#define STOUGHTON1004LIB_SOCKET_H

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
    Socket();
    /**
     * Create a TCP socket, connected to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     */
    Socket(const std::string& hostname, int port);

    /**
     * Close the connection 
     */
    void close();
    /**
     * Connect to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     */
    void connect(const std::string& hostname, int port);
    /**
     * Write the message to the connection
     * @param   msg     Message to be written
     */
    void write(const std::string& msg);
    /**
     * Reads messages from the connection.  Reading stops when either 
     * there is nothing left or the number of bytes given has been read.  
     * If there is nothing to read when the function is called, it will 
     * hang until something is available to be read.
     * @param   nBytes  Number of bytes to read
     * @return  Message of at most nBytes length
     */
    std::string read(int nBytes);
    /**
     * Read characters from the connection until a newline (\n), 
     * return carriage (\r), or return carriage followed by new line (\r\n) 
     * is read.  The message will not contain the end of line characters
     * @return  A line of characters from the connection
     */
    std::string readLine();

    /**
     * Returns the connected state of the socket
     * @return  True if the socket is connected
     */
    bool isConnected() const;

private:
    bool isClosed                   ///< Stores the closed state
    bool isConnected                ///< Store the connected state
    int tcpSocket;                  ///< Socket file descriptor
    sockaddr_in connectionInfo;     ///< Information about the connection

    friend class ServerSocket;
};  //class Socket

}   //namespace Stoughton1004Lib

#endif
