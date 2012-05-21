#ifndef STOUGHTON1004LIB_DATAGRAMPACKET_H
#define STOUGHTON1004LIB_DATAGRAMPACKET_H

#include <string>

namespace Stoughton1004Lib {

class DatagramPacket {
public:
    DatagramPacket();
    DatagramPacket(std::string address, int port)

    std::string getAddress() const;
    int getPort() const;
    std::string getData() const;

    DatagramPacket& setAddress(std::string address);
    DatagramPacket& setPort(int port);
    DatagramPacket& setData(std::string data);

private:
    std::string data;
    std::string address;
    int port;
};  //class DatagramPacket

}

#endif  //STOUGHTON1004LIB_DATAGRAMPACKET_H
