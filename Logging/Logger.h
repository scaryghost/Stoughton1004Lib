#ifndef STOUGHTON1004LIB_LOGGER_H
#define STOUGHTON1004LIB_LOGGER_H

#include "Stoughton1004Lib/Logging/Handler.h"
#include "Stoughton1004Lib/Logging/Level.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace Stoughton1004Lib {

/**
 * Logs messages, filtered by level.  The messages are passed through each log handler
 * @author etsai
 */
class Logger {
public:
    /**
     * Get the logger object associated with the given name
     * @param   loggerName  Name of the logger object
     * @return  Logger object of the given name
     */
    static Logger* getLogger(const std::string &loggerName);

    /**
     * Add a handler.  Users are expected to free any resources from the Handler object
     * @param   handler     Desired handler to pair with the logger
     */
    void addHandler(Handler *handler);
    /**
     * Sets the logging level
     * @param   newLevel    New level of the logger
     */
    void setLevel(Level newLevel);
    /**
     * Log a message of the specified level.  If a message's log level is below the set level, 
     * the message will not be passed on to the handlers
     * @param   level   The message's log level
     * @param   msg     Message to log
     */
    void log(Level level, const std::string &msg);

private:
    static std::unordered_map<std::string, Logger> loggers;     ///< Map of all loggers created

    /**
     * Constructs a logger with log level set to INFO.
     * Constructor is private so users must use the getLogger function
     */
    Logger();

    std::vector<Handler*> handlers;     ///< List of handlers tied to the logger
    Level level                         ///< Logging level of the logger

};  //class Logger

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_LOGGER_H