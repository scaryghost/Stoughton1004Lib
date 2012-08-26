#include "Stoughton1004Lib/Network/ServerSocket.h"

#include <sstream>

namespace Stoughton1004Lib {

using std::stringstream;

ServerSocket::ServerSocket() throw(S1004LibException) {
    init();
}

ServerSocket::ServerSocket(int port) throw(S1004LibException) {
    init();
    bind(port);
}

void ServerSocket::init() throw(S1004LibException) {
    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw S1004LibException("Cannot create TCP Socket");
    }
    bound= false;
    closed= false;
}

void ServerSocket::bind(int port) throw(S1004LibException) {
    if (closed) {
        throw S1004LibException("Cannot bind to port: server socket is closed");
    }
    if (bound) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Socket already bound to port " << ntohs(serverInfo.sin_port);
        throw S1004LibException(errorMsg.str());
    }

    serverInfo.sin_family= AF_INET;
    serverInfo.sin_addr.s_addr= INADDR_ANY;
    serverInfo.sin_port= htons(port);

    if (::bind(tcpSocket, (sockaddr *) &serverInfo, sizeof(serverInfo)) < 0) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Cannot bind to port " << port;
        throw S1004LibException(errorMsg.str());
    }
    listen(tcpSocket, 5);
    bound= true;
}

Socket ServerSocket::accept() throw(S1004LibException) {
    if (!bound) {
        throw S1004LibException("Server socket not bound to a port");
    }
    if (closed) {
        throw S1004LibException("Cannot accept connections: server socket is closed");
    }

    int clientfd;
    sockaddr_in clientAddr;
    unsigned int structSize= sizeof(clientAddr);


    clientfd= ::accept(tcpSocket, (sockaddr *) &clientAddr, &structSize);
    if (clientfd < 0) {
        throw S1004LibException("Cannot accept connection");
    }
    return Socket(clientfd, &clientAddr);
}

void ServerSocket::close() {
    ::close(tcpSocket);
    closed= true;
}

bool ServerSocket::isBound() const {
    return bound;
}

bool ServerSocket::isClosed() const {
    return closed;
}

}
