#ifndef STOUGHTON1004LIB_INETADDRESS_H
#define STOUGHTON1004LIB_INETADDRESS_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"

#include <netinet/in.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Stoughton1004Lib {

/**
 * Manages host name lookups, mapping host names to ip addresses.  
 * The functionality is based off the Java class of the same name
 * @author etsai
 */
class InetAddress {
public:
    /**
     * Get a list of all IP addresses of the given host name
     * @param   hostName    Host name to lookup
     * @return  All IP addresses of the host name
     * @throw   S1004LibException   If an invalid host name is given
     */
    static const std::vector<InetAddress>& getByName(std::string hostName) throw(S1004LibException);

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
    /** Cache of successful host name lookups */
    static std::unordered_map<std::string, std::vector<InetAddress> > resultsCache;

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
