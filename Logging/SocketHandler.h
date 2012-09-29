#ifndef STOUGHTON1004LIB_SOCKETHANDLER_H
#define STOUGHTON1004LIB_SOCKETHANDLER_H

#include "Stoughton1004Lib/Logging/Handler.h"
#include "Stoughton1004Lib/Network/DatagramSocket.h"
#include "Stoughton1004Lib/Network/DatagramPacket.h"
#include "Stoughton1004Lib/Network/Socket.h"
#include <string>

namespace Stoughton1004Lib {

class SocketHandler : public Handler {
public:
    enum Mode {
        TCP,
        UDP
    };

    SocketHandler(const std::string hostname, int port, Mode mode= TCP);
    ~SocketHandler();

    virtual bool publish(const std::string &msg);
    virtual void close();

private:
    Socket *tcpSocket;
    DatagramSocket *udpSocket;
    DatagramPacket *packet;
};

}


#endif