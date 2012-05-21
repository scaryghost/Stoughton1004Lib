#ifndef STOUGHTON1004LIB_DATAGRAMPACKET_H
#define STOUGHTON1004LIB_DATAGRAMPACKET_H

#include <string>

namespace Stoughton1004Lib {

/**
 * Stores information about the udp packet either to be sent or received
 * @author etsai
 */
class DatagramPacket {
public:
    /**
     * Construct a DatagramPacket storing the given number of bytes
     * @param   length  Number of bytes the packet stores
     */
    DatagramPacket(int length);
    /**
     * Construct a DatagramPacket storing the given number of bytes, 
     * and broadcasting to the given remote address, and port
     * @param   length      Number of bytes the packet stores
     * @param   address     Remote address the packet will be sent to
     * @param   port        Remote port to use
     */
    DatagramPacket(int length, std::string address, int port);

    /**
     * Get the ip address the datagram came from or the remost host to send to
     * @return  Address the datagram came from or remote host to send to
     */
    std::string getAddress() const;
    /**
     * Get the port the datagram came from or the remost host to send to
     * @return  Port the datagram came from or the remost host to send to
     */
    int getPort() const;
    /**
     * Get the data the packet contains
     * @return  Data the packet conatins
     */
    std::string getData() const;
    /**
     * Get the length of the data to be sent or received
     * @return Length of the data to be sent or received
     */
    unsigned int getLength() const;

    /**
     * Sets the address of the machine the packet is to be sent to
     * @param   address     IP address or hostname of the remote machine
     */
    DatagramPacket& setAddress(std::string address);
    /**
     * Sets the port of the maching the packet is to be sent to
     * @param   port        Port number of the remote machine
     */
    DatagramPacket& setPort(int port);
    /**
     * Sets the data the packet is sending.  This will update the length 
     * of the packet.
     * @param   data        Data buffer to send
     */
    DatagramPacket& setData(std::string data);
    /**
     * Set the length of the data the packet will be storing
     * @param   length      Length of the data buffer
     */
    DatagramPacket& setLength(int length);

private:
    std::string data;       ///< Data buffer of the packet
    std::string address;    ///< Address of the remote machine the packet came from or to be sent to
    int port;               ///< Port number of the remote machine the packet came from or be sent to
    int length;             ///< Length of the data buffer
};  //class DatagramPacket

}

#endif  //STOUGHTON1004LIB_DATAGRAMPACKET_H
