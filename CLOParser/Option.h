#ifndef STOUGHTON1004LIB_OPTION_H
#define STOUGHTON1004LIB_OPTION_H

#include <string>

namespace Stoughton1004Lib {

/**
 * Container for a command line option and its attributes
 * @author etsai
 */
class Option {
public:
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
    
private:
    std::string optName;        ///< Short name of the option
    std::string description;    ///< Description of the option
    std::string argName;        ///< Argument name
    std::string longOpt;        ///< Long name of the option
    bool required;              ///< True if option is required
    char separator;             ///< Character separator for arguments
    int args;                   ///< Max number of arguments to pass
};  //class Option

}   //namespace Stoughton1004Lib

#endif
