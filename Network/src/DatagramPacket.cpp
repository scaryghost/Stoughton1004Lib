#include "Stoughton1004Lib/Network/DatagramPacket.h"

namespace Stoughton1004Lib {

using std::string;

DatagramPacket::DatagramPacket(int length) {
    port= -1;
    this->length= length;
}

DatagramPacket::DatagramPacket(int length, std::string address, int port) {
    this->length= length;
    this->address= address;
    this->port= port;
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

unsigned int DatagramPacket::getLength() const {
    return length;
}

DatagramPacket& DatagramPacket::setAddress(std::string address) {
    this->address= address;
    return *this;
}

DatagramPacket& DatagramPacket::setPort(int port) {
    this->port= port;
    return *this;
}

DatagramPacket& DatagramPacket::setData(std::string data) {
    length= data.length();
    this->data.assign(data, 0, length);
    return *this;
}

DatagramPacket& DatagramPacket::setLength(int length) {
    this->length= length;
    return *this;
}

}
