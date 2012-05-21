#ifndef STOUGHTON1004LIB_S1004LIBEXCEPTION_H
#define STOUGHTON1004LIB_S1004LIBEXCEPTION_H

#include <exception>
#include <string>

namespace Stoughton1004Lib {

/**
 * Custom exception class for the Stoughton1004 library.
 * @author etsai
 */
class S1004LibException : public std::exception {
public:
    /**
     * Create exception with given error message
     * @param   msg     Error message
     */
    S1004LibException(const std::string& msg) {
        this->msg= msg;
    }
    ~S1004LibException() throw() {
    }

    /**
     * Get the error message
     * @return  Error message for the exception
     */
    const char* what() const throw() {
        return msg.c_str();
    }

private:
    std::string msg;        ///< Stores the error message
};  //class S1004LibException

}   //namespace Stoughton1004Lib

#endif //STOUGHTON1004LIB_S1004LIBEXCEPTION_H
