#include "Stoughton1004Lib/Network/ServerSocket.h"

#include <sstream>

namespace Stoughton1004Lib {

using std::stringstream;

ServerSocket::ServerSocket() throw(S1004LibException) {
    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw S1004LibException("Cannot create TCP Socket");
    }
    isBound= false;
    isClosed= false;
}

ServerSocket::ServerSocket(int port) : ServerSocket() throw(S1004LibException) {
    bind(port);
}

void ServerSocket::bind(int port) throw(S1004LibException) {
    if (isClosed) {
        throw S1004LibException("Cannot bind to port: server socket is closed");
    }
    if (isBound) {
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
    isBound= true;
}

Socket ServerSocket::accept() throw(S1004LibException) {
    if (!isBound) {
        throw S1004LibException("Server socket not bound to a port");
    }
    if (isClosed) {
        throw S1004LibException("Cannot accept connections: server socket is closed");
    }

    int clientfd;
    sockaddr_in clientAddr;
    int structSize= sizeof(client);

    clientfd= ::accept(tcpSocket, (sockaddr *) &clientAddr, &structSize);
    if (clientfd < 0) {
        throw S1004LibException("Cannot accept connection");
    }
    return Socket(clientfd, &clientAddr);
}

void ServerSocket::close() {
    close(tcpSocket);
    isClosed= true;
}

bool ServerSocket::isBound() const {
    return isBound;
}

bool ServerSocket::isClosed() const {
    return isClosed;
}

}
