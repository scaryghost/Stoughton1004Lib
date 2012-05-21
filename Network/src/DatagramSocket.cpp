#include "Stoughton1004Lib/Network/DatagramSocket.h"

#include <cstdlib>
#include <ctime>
#include <sstream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace Stoughton1004Lib {

using std::rand;
using std::srand;
using std::stringstream;
using std::time;

DatagramSocket::DatagramSocket() {
    udpSocket= socket(AF_INET, SOCK_DGRAM, 0);
    
    if (udpSocket < 0) {
        throw S1004LibException("Error creating DatagramSocket");
    }
}

void DatagramSocket::bind() {
    bool found= false;
    int port, offset;

    srand(time(NULL));
    port= rand() % 20000 + 30000;
    offset= 0;
    do {
        try {
            bind(port + offset);
            found= true;
        } catch (S1004LibException &e) {
            offset++;
        }
    } while(!found && offset < 20);

    if (!found) {
        stringstream msg(stringstream::out);

        msg << "Error binding port between [ " << port << "," << port + offset - 1 << "]";
        throw S1004LibException(msg.str());
    }

}

void DatagramSocket::bind(int port) {
    socketInfo.sin_family= AF_INET;
    socketInfo.sin_addr.s_addr= INADDR_ANY;
    socketInfo.sin_port= htons(port);

    if (bind(udpSocket, (struct sockaddr *) &socketInfo, sizeof(socketInfo)) < 0) {
        stringstream msg(stringstream::out);

        msg << "Error binding to port " << port;
        throw S1004LibException(msg.str());
    }
}

void DatagramSocket::receive(DatagramPacket& packet) {
    sockaddr_in sender;
    int nBytes;
    char buffer[1025], senderAddr[17];
    string data;
    
    do {
        nBytes= recvfrom(udpSocket, buffer, sizeof(buffer)-1, 0, (struct sockaddr *) &sender, sizeof(sender));

        if (nBytes < 0) {
            throw S1004LibException("Error receiving packet");
        }
        buffer[nBytes]= '\0';
        data+= buffer;
    } while (data.size() < packet.length() && nBytes == 1024);

    inet_ntop(AF_INET, &sender.sin_addr, senderAddr, sizeof(senderAddr));
    packet.setData(data).setAddress(inet_ntoa(senderAddr)).setPort(ntohs(sender.sin_port));
}

void DatagramSocket::send(const DatagramPacket& packet) {
    sockaddr_in recipient;
    int nBytes;

    inet_pton(AF_INET, packet.getAddress().c_str(), &(recipient.sin_addr));
    recipient.sin_port= htos(packet.getPort());
    nBytes= sendto(udpSocket, packet.getData().c_str(), packet.getLength(), 0, (struct sockaddr *) &recipient, sizeof(recipient));

    if (nBytes < 0) {
        stringstream msg(stringstream::out);

        msg << "Error sending packet to " << packet.getAddress() << ":" << packet.getPort();
        throw S1004LibException(msg.str());
    }
}

int DatagramSocket::getLocalPort() const {
    return ntohs(socketInfo.sin_port);
}

}

