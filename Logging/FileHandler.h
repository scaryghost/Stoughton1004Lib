#ifndef STOUGHTON1004LIB_FILEANDLER_H
#define STOUGHTON1004LIB_FILEHANDLER_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/Logging/Handler.h"

#include <fstream>
#include <string>

namespace Stoughton1004Lib {

class FileHandler : public Handler {
public:
    FileHandler() throw(S1004LibException);
    FileHandler(const std::string filename) throw(S1004LibException);
    ~FileHandler();

    virtual bool publish(const std::string &msg);
    virtual void close();

private:
    void open() throw(S1004LibException);

    std::string filename;
    std::ofstream fd;
};

}

#endif