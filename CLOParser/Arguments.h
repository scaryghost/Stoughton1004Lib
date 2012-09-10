#ifndef STOUGHTON1004LIB_ARGUMENTS_H
#define STOUGHTON1004LIB_ARGUMENTS_H

#include <vector>

namespace Stoughton1004Lib {

/**
 * Collection of parsed arguments for an Option
 * @author etsai
 */
class Arguments {
public:
    /**
     * Construct object with no arguments
     */
    Arguments();

    /**
     * Split the string around the separator and add the separated 
     * parts to the collection
     * @param   argStr      String containing option arguments
     * @param   separator   Character to split the argument string
     */
    void addArgs(const std::string& argStr, char separator);

    /**
     * Get the number of arguments
     * @return  Number of arguments
     */
    unsigned int size() const;
    /**
     * Get the argument at the index as a double
     * @param   index   Argument index to return
     * @return  Argument as a double
     */
    double asDouble(int index) const;
    /**
     * Get the argument at the index as an integer
     * @param   index   Argument index to return
     * @return  Argument as an integer
     */
    int asInteger(int index) const;
    /**
     * Get the argument at the index as a string
     * @param   index   Argument index to return
     * @return  Argument as a string
     */
    std::string asString(int index) const;

private:
    std::vector<string> argList;    ///< Collection of argument values
};  //class Arguments

}   //namespace Stoughton1004Lib

#endif
