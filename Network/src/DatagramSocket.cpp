#include "Stoughton1004Lib/Network/DatagramSocket.h"
#include "Stoughton1004Lib/Network/InetAddress.h"

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>

#ifdef WIN32
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

typedef int socklen_t;
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

namespace Stoughton1004Lib {

using std::rand;
using std::srand;
using std::string;
using std::stringstream;
using std::time;
using std::vector;

DatagramSocket::DatagramSocket() throw(S1004LibException) {
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw S1004LibException("Error initializing Winsock");
    }
#endif
    udpSocket= socket(AF_INET, SOCK_DGRAM, 0);
    
    if (udpSocket < 0) {
        throw S1004LibException("Error creating DatagramSocket");
    }
}

DatagramSocket::~DatagramSocket() throw(S1004LibException) {
    int status;

#ifdef WIN32
    status= closesocket(udpSocket);
#else
    status= close(udpSocket);
#endif
    if (status != 0) throw S1004LibException("Error closing DatagramSocket");
}

void DatagramSocket::bind() throw(S1004LibException) {
    bool found= false;
    int port, offset;

    srand((unsigned int)time(NULL));
    port= rand() % 20000 + 30000;
    offset= 0;
    do {
        try {
            bind(port + offset);
            found= true;
        } catch (S1004LibException) {
            offset++;
        }
    } while(!found && offset < 20);

    if (!found) {
        stringstream msg(stringstream::out);

        msg << "Error binding port between [ " << port << "," << port + offset - 1 << "]";
        throw S1004LibException(msg.str());
    }

}

void DatagramSocket::bind(int port) throw(S1004LibException) {
    socketInfo.sin_family= AF_INET;
    socketInfo.sin_addr.s_addr= INADDR_ANY;
    socketInfo.sin_port= htons(port);

    if (::bind(udpSocket, (struct sockaddr *) &socketInfo, sizeof(socketInfo)) < 0) {
        stringstream msg(stringstream::out);

        msg << "Error binding to port " << port;
        throw S1004LibException(msg.str());
    }
}

void DatagramSocket::receive(DatagramPacket& packet) throw(S1004LibException) {
    sockaddr_in sender;
    int nBytes;
    socklen_t senderLength= sizeof(sender);
    char buffer[1025];
    string data;
    
    do {
        nBytes= recvfrom(udpSocket, buffer, sizeof(buffer)-1, 0, (struct sockaddr *) &sender, &senderLength);

        if (nBytes < 0) {
            throw S1004LibException("Error receiving packet");
        }
        buffer[nBytes]= '\0';
        data+= buffer;
    } while (data.size() < packet.getLength() && nBytes == sizeof(buffer)-1);
    packet.setData(data).setAddress(inet_ntoa(sender.sin_addr)).setPort(ntohs(sender.sin_port));
}

void DatagramSocket::send(const DatagramPacket& packet) throw(S1004LibException) {
    bool success= true;
    sockaddr_in recipient;

    recipient.sin_family= AF_INET;
    recipient.sin_port= htons(packet.getPort());
    vector<InetAddress> results= InetAddress::getByName(packet.getAddress());

    for(auto it= results.begin(); it != results.end(); it++) {
        int nBytes;
        inet_pton(recipient.sin_family, it->getHostAddress().c_str(), &(recipient.sin_addr));
        nBytes= sendto(udpSocket, packet.getData().c_str(), packet.getLength(), 0, 
            (struct sockaddr *) &recipient, sizeof(recipient));

        success= success && (nBytes >= 0);
    }
    if (!success) {
        stringstream msg(stringstream::out);

        msg << "Error sending packet to " << packet.getAddress() << ":" << packet.getPort();
        throw S1004LibException(msg.str());
    }

}

int DatagramSocket::getLocalPort() const {
    return ntohs(socketInfo.sin_port);
}

}

