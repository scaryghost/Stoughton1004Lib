#ifndef STOUGHTON1004LIB_OPTION_H
#define STOUGHTON1004LIB_OPTION_H

#include "Stoughton1004Lib/CLI/Arguments.h"

#include <functional>
#include <string>

namespace Stoughton1004Lib {

class CLIBuilder;

/**
 * Container for a command line option and its attributes
 * @author etsai
 */
class Option {
public:
    /** Create a type name for the Option's callback action */
    typedef std::function<void (Arguments)> OptCallback;

    /**
     * Create an option that takes no arguments
     * @param   optName     Name of the argument
     * @param   required    True if the option is required.  Default value is false
     */
    Option(const std::string& optName, bool required= false);
    /**
     * Create an option that takes additional arguments
     * @param   optName     Name of the argument
     * @param   separator   Character to separate the arguments
     * @param   args        Number of arguments
     * @param   required    True if option is required.  Default value is false
     */
    Option(const std::string& optName, char separator, int args, bool required= false);
    
    /**
     * Sets the description
     * @param   description     Description of the option
     * @return  Reference to the calling object
     */
    Option& withDescription(const std::string& description);
    /**
     * Sets the argument name
     * @param   argName     Name of the argument
     * @return  Reference to the calling object
     */
    Option& withArgName(const std::string& argName);
    /**
     * Sets the long option name
     * @param   longOpt     Long name of the option
     * @return  Reference to the calling object
     */
    Option& withLongOpt(const std::string& longOpt);
    /**
     * Sets the callback action
     * @param   callback    Lambda containing the action to be executed
     * @return  Reference to the calling object
     */
    Option& withCallback(const OptCallback& callback);

private:
    std::string optName;        ///< Short name of the option
    char separator;             ///< Character separator for arguments
    int args;                   ///< Max number of arguments to pass
    bool required;              ///< True if option is required

    std::string description;    ///< Description of the option
    std::string argName;        ///< Argument name
    std::string longOpt;        ///< Long name of the option
    OptCallback callback;       ///< Callback action to be run if the option is matched

    friend class CLIBuilder;
};  //class Option

}   //namespace Stoughton1004Lib

#endif
