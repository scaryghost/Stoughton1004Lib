#include "Stoughton1004Lib/CLI/CLIBuilder.h"

#include <cstdlib>
#include <iostream>

namespace Stoughton1004Lib {

using std::cout;
using std::endl;
using std::exit;
using std::string;

CLIBuilder CLIBuilder::instance;

CLIBuilder* CLIBuilder::getBuilder() {
    return &instance;
}

CLIBuilder& CLIBuilder::addOption(const Option& opt) throw(S1004LibException) {
    if (options.count(opt.optName) != 0 || options.count(opt.longOpt) != 0) {
        throw S1004LibException("Option already registered");
    }
    options[opt.optName]= opt;
    if (!opt.longOpt.empty()) {
        options[opt.longOpt]= opt;
    }
    return *this;
}

CLIBuilder& CLIBuilder::setUsage(const string& usage) {
    this->usage= usage;
    return *this;
}

void CLIBuilder::parse(int argc, char **argv) {
    int i;
    
    while(i < argc) {
        if (argv[i][0] == '-') {
            Option *opt= &options[argv[i]];
            Arguments args;

            if (opt->args > 0) {
                args.addArgs(argv[i+1], opt->separator);
                i+= 2;
            } else {
                i++;
            }
            opt->callback(args);
            options.erase(argv[i]);
        } else {
            i++;
        }
    }

    for(auto it= options.begin(); it != options.end(); it++) {
        if ((it->second).required) {
            throw S1004LibException("Required option was not given");
        }
    }
}

void CLIBuilder::displayUsage() {
    cout << "usage: " << usage << endl;
    for(auto it= options.begin(); it != options.end(); it++) {
        cout << it->first << "\t" << (it->second).description << endl;
    }
    exit(0);
}

CLIBuilder::CLIBuilder() {
}

}
