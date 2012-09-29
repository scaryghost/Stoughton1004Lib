#include "Stoughton1004Lib/Network/InetAddress.h"
#include "Stoughton1004Lib/Logging/FileHandler.h"

#include <ctime>

namespace Stoughton1004Lib {

using std::string;
using std::time_t;
using std::tm;

FileHandler::FileHandler() throw(S1004LibException) : Handler(Level::INFO) {
    time_t curr;
    tm* timeInfo;
    const char* format= "_%Y-%m-%d_%H-%M-%S";
    char timeStamp[80];

    time(&curr);
    timeInfo= localtime(&curr);
    strftime(timeStamp, sizeof(timeStamp), format, timeInfo);
    filename= InetAddress::getLocalHostName() + timeStamp + ".log";

    open();
}

FileHandler::FileHandler(const string filename) throw(S1004LibException) : Handler(Level::INFO) {
    this->filename= filename;
    open();
}

FileHandler::~FileHandler() {
    close();
}

void FileHandler::open() throw(S1004LibException) {
    fd.open(filename.c_str());
    if (!fd) {
        throw S1004LibException("Error opening file: " + filename + " for logging");
    }
}

bool FileHandler::publish(const string &msg) {
    fd << msg << "\n";
    return true;
}

void FileHandler::close() {
    fd.close();
}

}