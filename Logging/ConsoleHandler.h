#ifndef STOUGHTON1004LIB_CONSOLEHANDLER_H
#define STOUGHTON1004LIB_CONSOLEHANDLER_H

#include "Stoughton1004Lib/Logging/Handler.h"

#include <iostream>

namespace Stoughton1004Lib {

class ConsoleHandler : public Handler {
public:
    ConsoleHandler() : Handler(Level::INFO) {}

    virtual bool publish(const std::string &msg) { std::cout << msg << std::endl; return true; }
    virtual void close() { return; }
};

}

#endif