#include "Stoughton1004Lib/Network/DatagramPacket.h"

namespace Stoughton1004Lib {

DatagramPacket::DatagramPacket() {
    port= -1;
}

DatagramPacket::DatagramPacket(std::string address, int port) {
    this.address= address;
    this.port= port;
}

std::string DatagramPacket::getAddress() const {
    return address;
}

int DatagramPacket::getPort() const {
    return port;
}

std::string DatagramPacket::getData() const {
    return data;
}

DatagramPacket& DatagramPacket::setAddress(std::string address) {
    this.address= address;
    return *this;
}

DatagramPacket& DatagramPacket::setPort(int port) {
    this.port= port;
    return *this;
}

DatagramPacket& DatagramPacket::setData(std::string data) {
    this.data= data;
    return *this;
}

}