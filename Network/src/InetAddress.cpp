#include "Stoughton1004Lib/Network/InetAddress.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace Stoughton1004Lib {

using std::string;
using std::vector;

static vector<InetAddress> InetAddress::getByName(std::string hostName) {
    vector<InetAddress> results;
    addrinfo hints, *res, *next;
    int err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_family= AF_INET;

    if ((err= getaddrinto(hostName.c_str(), NULL, &hints, &res)) != 0) {
    }

    for(next= res; next != NULL; next= next->ai_next) {
        INetAddress addr;
        addr.rawIpAddr= ((sockaddr_int *)(next->ai_addr))->sin_addr.s_addr;
        addr.ipAddr= inet_ntoa(addr);
        addr.hostName= hostName;
        results.push_back(addr);
    }

    return results;
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

