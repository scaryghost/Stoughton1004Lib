#ifndef STOUGHTON1004LIB_HANDLER_H
#define STOUGHTON1004LIB_HANDLER_H

#include "Stoughton1004Lib/Logging/Level.h"
#include <string>

namespace Stoughton1004Lib {

/**
 * Abstract class defining the functionality for the log handlers.  The log handler 
 * processes the messages logged by the code and can have their own separate 
 * logging level from its Logger owner.
 * @author etsai
 */
class Handler {
public:
    /**
     * Overloaded class destructor
     * @see close
     */
    virtual ~Handler() {}

    /**
     * Publish the messages from the logger.  The boolean return type is used 
     * as a way to filter handlers without using an if statement
     * @param   msg     Message to publish
     * @return Always returns true
     */
    virtual bool publish(const std::string &msg)= 0;
    /**
     * Close the handler and deallocated resources
     */
    virtual void close()= 0;
    /**
     * Set the logging level for the handler
     * @param   level   Logging level to set
     */
    void setLevel(Level newLevel) { level= newLevel; }

    /**
     * Get the logging level for the handler
     * @return Log level
     */
    Level getLevel() const { return level; }

protected:
    /**
     * Constructs a Handler with the specified level
     * @param   level   Logging level of the object
     */
    Handler(Level level) { this->level= level; }

    Level level;    ///< Logging level of the handler
};

}

#endif //STOUGHTON1004LIB_HANDLER_H
