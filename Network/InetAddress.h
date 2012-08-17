#ifndef STOUGHTON1004LIB_DATAGRAMSOCKET_H
#define STOUGHTON1004LIB_DATAGRAMSOCKET_H

#include <netinet/in.h>
#include <string>
#include <vector>

namespace Stoughton1004Lib {

class InetAddress {
public:
    /**
     * Get a list of all IP addresses of the given host name
     * @param   hostName    Host name to lookup
     * @return  All IP addresses of the host name
     */
    static std::vector<InetAddress> getByName(std::string hostName);

    /**
     * Get the raw IP address of the object
     * @return raw IP address
     */
    in_addr getAddress() const;
    /**
     * Get the IP address as text
     * @return textual IP address
     */
    std::string getHostAddress() const;
    /**
     * Get the host name of the IP address
     * @return host name
     */
    std::string getHostName() const;

private:
    /**
     * Default constructor.
     * Set as private so users cannot create their own InetAddress object
     * outside of using the static function
     */
    InetAddress();

    std::string hostName;       ///< Host name 
    std::string ipAddr;         ///< Text version of the ip address
    in_addr rawIpAddr;          ///< Raw IP address
};

}

#endif
