#include "Stoughton1004Lib/CLOParser/Option.h"

namespace Stoughton1004Lib {

Option::Option(const std::string& optName, bool required= false) : 
    optName(optName), separator(0), args(0), required(required) {
}

Option::Option(const std::string& optName, char separator, int args, bool required= false) : 
    optName(optName), separator(separator), args(args), required(required) {
}
    
Option& Option::withDescription(const std::string& description) {
    this->description= description;
    return *this;
}

Option& Option::withArgName(const std::string& argName) {
    this->argName= argName;
    return *this;
}

Option& Option::withLongOpt(const std::string& longOpt) {
    this->longOpt= longOpt;
    return *this;
}

Option& withCallback(const OptCallback& callback) {
    this->callback= callback;
    return *this;
}

bool operator <(const Option& lhs, const Options& rhs) {
    return lhs.optName < rhs.optName;
}

}
