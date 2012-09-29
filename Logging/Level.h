#ifndef STOUGHTON1004LIB_LEVEL_H
#define STOUGHTON1004LIB_LEVEL_H

namespace Stoughton1004Lib {

/**
 * Logging levels that set how much detail is captured 
 * by the logging utilities
 */
enum Level {
    ALL,        ///< All messages should be logged
    FINEST,     ///< Provides the most detailed tracing
    FINER,      ///< Provides more detailed tracing
    FINE,       ///< Provides some tracing
    CONFIG,     ///< Configuration messages
    INFO,       ///< Informational messages
    WARNING,    ///< Indicates potential problems
    SEVERE     ///< Serious problem or failure 
};

}

#endif //STOUGHTON1004LIB_LEVEL_H
