#ifndef STOUGHTON1004LIB_CLIBUILDER_H
#define STOUGHTON1004LIB_CLIBUILDER_H

#include "Stoughton1004Lib/Exception/S1004LibException.h"
#include "Stoughton1004Lib/CLI/Option.h"

#include <map>
#include <string>

namespace Stoughton1004Lib {

class CLIBuilder {
public:
    static CLIBuilder* getBuilder();

    CLIBuilder& addOption(const Option& opt) throw(S1004LibException);
    CLIBuilder& setUsage(const std::string& usage);

    void parse(int argc, char **argv);
    void usage();

private:
    CLIBuilder();

    static CLIBuilder instance;
    std::map<std::string, Option> options;
    std::string usage;
};

}

#endif
