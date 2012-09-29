#ifndef STOUGHTON1004LIB_FILEHANDLER_H
#define STOUGHTON1004LIB_FILEHANDLER_H

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/Logging/Handler.h"

#include <fstream>
#include <string>

namespace Stoughton1004Lib {

/**
 * Sends messages to a file
 * @author etsai
 */
class FileHandler : public Handler {
public:
    /**
     * Create a FileHandler with a generated log name based on the current date and time
     * @throws  S1004LibException   If the file failed to open
     */
    FileHandler() throw(S1004LibException);
    /**
     * Create a FileHandler, writing to the given filename.  If the file exists, it will 
     * be overwritten
     * @param   filename    Name of the log file to write to.
     * @throw   S1004LibException   If the file failed to open
     */
    FileHandler(const std::string filename) throw(S1004LibException);
    /**
     * Close file resources
     */
    ~FileHandler();

    virtual bool publish(const std::string &msg);
    virtual void close();

private:
    /**
     * Open the log file for writing.  Need this function here because not all compilers support 
     * constructor delegation
     * @throw   S1004LibException   If the file failed to open
     */
    void open() throw(S1004LibException);

    std::string filename;       ///< Name of the file to write to
    std::ofstream fd;           ///< Log's file descriptor
};  //class FileHandler

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_FILEHANDLER_H