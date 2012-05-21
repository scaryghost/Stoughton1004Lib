#include "Stoughton1004Lib/Network/DatagramSocket.h"

#include <cstdlib>
#include <ctime>
#include <stdexcept>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace Stoughton1004Lib {

using std::rand;
using std::runtime_error;
using std::srand;
using std::time;

DatagramSocket::DatagramSocket() {
    udpSocket= socket(AF_INET, SOCK_DGRAM, 0);
    
    if (udpSocket < 0) {
        //throw exception
    }
}

void DatagramSocket::bind() {
    throw runtime_error("Not yet implemented!");
}

void DatagramSocket::bind(int port) {
    socketInfo.sin_family= AF_INET;
    socketInfo.sin_addr.s_addr= INADDR_ANY;
    socketInfo.sin_port= htons(port);

    if (bind(udpSocket, (struct sockaddr *) &socketInfo, sizeof(socketInfo)) < 0) {
        //throw exception
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
            //throw exception
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
    sendto(udpSocket, packet.getData().c_str(), packet.getLength(), 0, (struct sockaddr *) &recipient, sizeof(recipient));
}

}

