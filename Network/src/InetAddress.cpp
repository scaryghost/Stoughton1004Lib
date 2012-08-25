#include "Stoughton1004Lib/Network/InetAddress.h"

#include <string.h>
#include <sys/types.h>

#ifndef WIN32
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#else
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

namespace Stoughton1004Lib {

using std::string;
using std::unordered_map;
using std::vector;

unordered_map<string, vector<InetAddress> > InetAddress::resultsCache;

const vector<InetAddress>& InetAddress::getByName(std::string hostName) throw(S1004LibException) {
    if (resultsCache.count(hostName) != 0) {
        return resultsCache[hostName];
    }

#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw S1004LibException("Error initializing Winsock");
    }
#endif

    vector<InetAddress> results;
    addrinfo hints, *res, *next;
    int err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_family= AF_INET;

    if ((err= getaddrinfo(hostName.c_str(), NULL, &hints, &res)) != 0) {
        throw S1004LibException("Invalid host name given: " + hostName);
    }

    for(next= res; next != NULL; next= next->ai_next) {
        InetAddress addr;
        addr.rawIpAddr.s_addr= ((sockaddr_in *)(next->ai_addr))->sin_addr.s_addr;
        addr.ipAddr= inet_ntoa(addr.rawIpAddr);
        addr.hostName= hostName;
        results.push_back(addr);
    }
    resultsCache[hostName]= results;

    return resultsCache[hostName];
}

InetAddress::InetAddress() {
}

in_addr InetAddress::getAddress() const {
    return rawIpAddr;
}

string InetAddress::getHostAddress() const {
    return ipAddr;
}

string InetAddress::getHostName() const {
    return hostName;
}

}
