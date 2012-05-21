#ifndef STOUGHTON1004LIB_S1004LIBEXCEPTION_H
#define STOUGHTON1004LIB_S1004LIBEXCEPTION_H

#include <exception>
#include <string>

namespace Stoughton1004Lib {

class S1004LibException : public std::exception {
public:
    S1004LibException(const std::string& msg) {
        this.msg= msg;
    }
    ~S1004LibException() throw() {
    }

    const char* what() const throw() {
        return msg.c_str();
    }

private:
    std::string msg;
};  //class S1004LibException

}   //namespace Stoughton1004Lib

#endif //STOUGHTON1004LIB_S1004LIBEXCEPTION_H
