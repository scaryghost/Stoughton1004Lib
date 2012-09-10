#include "Stoughton1004Lib/Network/Socket.h"
#include "Stoughton1004Lib/Network/InetAddress.h"

#ifdef WIN32
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#endif
#include <sstream>
#include <vector>

namespace Stoughton1004Lib {

using std::string;
using std::stringstream;
using std::vector;

Socket::Socket() throw(S1004LibException) {
    init();
}

Socket::Socket(const string& hostname, int port) throw(S1004LibException) {
    init();
    connect(hostname, port);
}

Socket::Socket(int tcpSocket, sockaddr_in *addr) {
    this->tcpSocket= tcpSocket;
    connectionInfo.sin_family= addr->sin_family;
    connectionInfo.sin_port= addr->sin_port;
    connectionInfo.sin_addr= addr->sin_addr;
    
    connected= true;
    closed= false;
#ifdef WIN32
    winsockCleanup= false;
#endif
}

Socket::~Socket() {
    close();
}

void Socket::init() throw(S1004LibException) {
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw S1004LibException("Error initializing Winsock");
    }
    winsockCleanup= true;
#endif

    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw S1004LibException("Cannot open TCP socket");
    }

    connected= false;
    closed= false;
}

void Socket::close() {
#ifdef WIN32
    closesocket(tcpSocket);
    if (winsockCleanup) {
        WSACleanup();
    }
#else
    ::close(tcpSocket);
#endif
    closed= true;
}

void Socket::connect(const string& hostname, int port) throw(S1004LibException) {
    if (closed) {
        throw S1004LibException("Socket is closed");
    }
    if (connected) {
        throw S1004LibException("Already connected to a remote machine");
    }

    bool success= false;
    vector<InetAddress> results= InetAddress::getByName(hostname);
    connectionInfo.sin_family= AF_INET;
    connectionInfo.sin_port= htons(port);

    for(auto it= results.begin(); !success && it != results.end(); it++) {
        int result;

        connectionInfo.sin_addr= it->getAddress();
        result= ::connect(tcpSocket,(sockaddr *) &connectionInfo, sizeof(connectionInfo));
        success= success || result >= 0;
    }
    if (!success) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Cannot connect to " << hostname << ":" << port;
        throw S1004LibException(errorMsg.str());
    }

    connected= true;
}

void Socket::write(const string& msg) throw(S1004LibException) {
    int nBytes;

#ifndef WIN32
    nBytes= ::write(tcpSocket, msg.c_str(), msg.length());
#else
    nBytes= send(tcpSocket, msg.c_str(), msg.length(), 0);
#endif
    if (nBytes < 0) {
        throw S1004LibException("Cannot write to socket");
    }
}

string Socket::read(unsigned int nBytes) throw(S1004LibException) {
    if (closed) {
        throw S1004LibException("Socket closed, cannot read");
    }
    if (!connected) {
        throw S1004LibException("Socket not connected, cannot read");
    }

    string msg;
    char buffer[2]= {'\0', '\0'};
    int readBytes;

    do {
#ifndef WIN32
        readBytes= ::read(tcpSocket, buffer, sizeof(buffer) - 1);
#else
        readBytes= recv(tcpSocket, buffer, sizeof(buffer) - 1, 0);
#endif

        if (readBytes < 0) {
            throw S1004LibException("Cannot read from socket");
        } else {
            /**
             * Throw out \n in a \r\n sequence.  The readLine function sets 
             * readCarriage to true if \r is read, then terminates.  This only 
             * applies to readLine.  A normal read will consume everything
             */
            if (!readCarriage || buffer[0] != '\n') {
                msg+= buffer;
            }
            readCarriage= false;
        }
    } while(msg.length() < nBytes && readBytes == sizeof(buffer)-1);

    return msg;
}

string Socket::readLine() throw(S1004LibException) {
    string msg, ch;
    auto terminate= [this](string ch) -> bool {
        readCarriage= ch == "\r";
        return readCarriage || ch == "\n";
    };

    while(!terminate((ch= read(1)))) {
        msg+= ch;
    }
    return msg;
}

bool Socket::isConnected() const {
    return connected;
}

int Socket::getPort() const {
    return ntohs(connectionInfo.sin_port);
}

string Socket::getAddress() const {
    return inet_ntoa(connectionInfo.sin_addr);
}

}
