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
     * @para    argv    Array of arguments passed in
     */
    void parse(int argc, char **argv);
    /**
     * Print the usage message, and then terminate
     */
    void usage();

private:
    CLIBuilder();                           ///< Default constructor

    static CLIBuilder instance;             ///< Singleton instance of the class
    std::map<std::string, Option> options;  ///< Map of added options
    std::string usage;                      ///< Usage message for the program
};  //class CLIBuilder

}   //namespace Stoughton1004Lib

#endif
