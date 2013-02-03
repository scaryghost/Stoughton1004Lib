#include "Stoughton1004Lib/Network/InetAddress.h"
#include "Stoughton1004Lib/Logging/FileHandler.h"

#include <ctime>

namespace Stoughton1004Lib {

using std::time_t;
using std::tm;

FileHandler::FileHandler() throw(S1004LibException) : Handler(Level::INFO) {
    time_t curr;
    const char* format= "_%Y-%m-%d_%H-%M-%S";
    char timeStamp[80];

    time(&curr);
#ifdef WIN32
    tm timeInfo;
    localtime_s(&timeInfo, &curr);
    strftime(timeStamp, sizeof(timeStamp), format, &timeInfo);
#else
    tm* timeInfo;
    timeInfo= localtime(&curr);
    strftime(timeStamp, sizeof(timeStamp), format, timeInfo);
#endif
    filename= InetAddress::getLocalHostName() + timeStamp + ".log";

    open();
}

FileHandler::FileHandler(const std::string filename) throw(S1004LibException) : Handler(Level::INFO) {
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

bool FileHandler::publish(const std::string &msg) {
    fd << msg << "\n";
    fd.flush();
    return true;
}

void FileHandler::close() {
    fd.close();
}

}
