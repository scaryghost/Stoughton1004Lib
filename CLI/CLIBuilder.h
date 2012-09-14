#ifndef STOUGHTON1004LIB_CLIBUILDER_H
#define STOUGHTON1004LIB_CLIBUILDER_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/CLI/Option.h"

#include <map>
#include <string>

namespace Stoughton1004Lib {

/**
 * Builder for processing command line arguments
 * @author etsai
 */
class CLIBuilder {
public:
    /**
     * Get the builder object
     * @return  CLIBuilder instance
     */
    static CLIBuilder* getBuilder();

    /**
     * Add an option to the collection
     * @param   opt     Option to add
     * @return  Reference to the calling object
     * @throw   S1004LibException   If a duplicate option has already been acted
     */
    CLIBuilder& addOption(const Option& opt) throw(S1004LibException);
    /**
     * Set the usage message
     * @param   usage   Usage description
     * @return  Reference to the calling object
     */
    CLIBuilder& setUsage(const std::string& usage);

    /**
     * Parse the command line arguments and execute the callback functions
     * @param   argc    Number of arguments
     * @param   argv    Array of arguments passed in
     * @throw   S1004LibException   If invalid option was passed in or not enough 
     * arguments were given for an option
     */
    void parse(int argc, char **argv) throw(S1004LibException);
    /**
     * Print the usage message, and then terminate
     */
    void displayUsage();

private:
    CLIBuilder();                           ///< Default constructor.  Hidden to make singleton

    static CLIBuilder instance;             ///< Single instance of the class
    std::map<std::string, Option> options;  ///< Map of added options
    std::string usage;                      ///< Usage message for the program
};  //class CLIBuilder

}   //namespace Stoughton1004Lib

#endif
