#include "Stoughton1004Lib/Network/Socket.h"

#include "Stoughton1004Lib/Network/InetAddress.h"
#include <sys/socket.h>
#include <sstream>
#include <vector>

namespace Stoughton1004Lib {

using std::string;
using std::stringstream;
using std::vector;

Socket::Socket() throw(S1004LibException) {
    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw S1004LibException("Cannot open TCP socket");
    }
    isConnected= false;
    isClosed= false;
}

Socket::Socket(const string& hostname, int port) : Socket() throw(S1004LibException) {
    connect(hostname, port);
}

Socket::Socket(int tcpSocket, sockaddr_in *addr) {
    this->tcpSocket= tcpSocket;
    connectionInfo.sin_family= addr->sin_family;
    connectionInfo.sin_port= addr->sin_port;
    connectionInfo.sin_addr= addr->sin_addr;
    
    isConnected= true;
    isClosed= false;
}

void Socket::close() {
    close(tcpSocket);
    isClosed= true;
}

void Socket::connect(const string& hostname, int port) throw(S1004LibException) {
    if (isClosed) {
        throw S1004LibException("Socket is closed");
    }

    bool success= false;
    vector<InetAddress> results= InetAddress::getByName(hostname);
    connectionInfo.sin_family= AF_INET;
    connectionInfo.sin_port= htons(port);

    for(auto it= results.begin(); !success && it != results.end(); it++) {
        int result;

        connectionInfo.sin_addr= it->getAddress();
        result= ::connect(tcpSocket,(sockaddr *) &connectionInfo, sizeof(connectionInfo));
        success= success || result > 0;
    }
    if (!success) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Cannot connect to " << hostname << ":" << port;
        throw S1004LibException(errorMsg.str());
    }

    isConnected= true;
}

void Socket::write(const string& msg) throw(S1004LibException) {
    int nBytes;

    nBytes= ::write(tcpSocket, msg.c_str(), msg.length());
    if (nBytes < 0) {
        throw S1004LibException("Cannot write to socket");
    }
}

string Socket::read(int nBytes) throw(S1004LibException) {
    if (isClosed) {
        throw S1004LibException("Socket closed, cannot read");
    }
    if (!isConnected) {
        throw S1004LibException("Socket not connected, cannot read");
    }

    string msg;
    char buffer[1025];
    int readBytes;

    do {
        readBytes= read(sockfd,buffer, sizeof(buffer)-1);

        if (readBytes < 0) {
            throw S1004LibException("Cannot read from socket");
        }

        buffer[readBytes]= '\0';
        msg+= buffer;
    } while(msg.length() < nBytes && readBytes == sizeof(buffer)-1);

    return msg;
}

string Socket::readLine() throw(S1004LibException) {
    if (isClosed) {
        throw S1004LibException("Socket closed, cannot read");
    }
    if (!isConnected) {
        throw S1004LibException("Socket not connected, cannot read");
    }

    string msg;
    char buffer[1025];
    int readBytes;
    bool terminate= false;

    while(!terminate) {
        readBytes= read(sockfd,buffer, sizeof(buffer)-1);

        if (readBytes < 0) {
            throw S1004LibException("Cannot read from socket");
        }

        buffer[readBytes]= '\0';
        terminate= (buffer[readBytes-1] == '\n' || buffer[readBytes-1] == '\r');
        if (terminate) {
            buffer[readBytes-1]= '\0';
            if (readBytes-2 >= 0 && buffer[readBytes-2]== '\r') {
                buffer[readBytes-2]= '\r';
            }
        }
        msg+= buffer;
    }
    return msg;
}

bool Socket::isConnected() const {
    return isConnected;
}

}
