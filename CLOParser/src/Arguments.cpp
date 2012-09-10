#include "Stoughton1004Lib/CLOParser/Arguments.h"

#include <cstdlib>

namespace Stoughton1004Lib {

using std::string;
using std::atoi;
using std::atof;

Arguments::Arguments() {
}

void Arguments::addArgs(const string& argStr, char separator) {
    unsigned int i= 0;
    string part;

    while(i < argStr.size()) {
        if (argStr[i] != separator) {
            part+= argStr[i];
        } else {
            argList.push_back(part);
            part.clear();
        }
        i++;
    }
    if (!part.empty()) {
        argList.push_back(part);
    }
}

unsigned int Arguments::size() const {
    return argList.size();
}

double Arguments::asDouble(int index) const {
    return atof(argList[index].c_str());
}

int Arguments::asInteger(int index) const {
    return atoi(argList[index].c_str());
}

string Arguments::asString(int index) const {
    return argList[index];
}

}
