#include "Stoughton1004Lib/Logging/SocketHandler.h"

namespace Stoughton1004Lib {

using std::string;

SocketHandler::SocketHandler(const string hostname, int port, Mode mode) {
    if (mode == TCP) {
        tcpSocket= new Socket(hostname, port);
        udpSocket= nullptr;
    } else  {
        tcpSocket= nullptr;
        udpSocket= new DatagramSocket();
        packet= new DatagramPacket(128);
    }
}

SocketHandler::~SocketHandler() {
    if (tcpSocket != nullptr)
        delete tcpSocket;
    if (udpSocket != nullptr)
        delete udpSocket;
    if (packet != nullptr)
        delete packet;
}


bool SocketHandler::publish(const string &msg) {
    if (tcpSocket != nullptr) {
        tcpSocket->write(msg+"\n");
    } else {
        packet->setLength(msg.size()).setData(msg);
        udpSocket->send(*packet);
    }
    return true;
}

void SocketHandler::close() {
    if (tcpSocket != nullptr) {
        tcpSocket->close();
    }
}

}