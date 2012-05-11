#ifndef STOUGHTON1004LIB_UNIQUEID_H
#define STOUGHTON1004LIB_UNIQUEID_H

#include <string>

namespace Stoughton1004Lib {

/**
 * UUID generator that creates a unique name and id.
 * Any class wanting to use this feature must inherit 
 * from the class and implement the getName function
 * @author etsai
 */
class UniqueId {
public:
    /**
     * Get the current numerical id
     * @return  Number of UUIDs created
     */
    static int getCurrentId();

    /**
     * Default constructor that increments the id counter
     */
    UniqueId();

    /**
     * Retrieves a unique name for the given id.
     * This is implemented by the deriving classes, providing 
     * a unique string id for its numerical counter part
     * @return  Unique name for the object
     */
    std::string virtual getName() const= 0;
    /**
     * Returns a unique numerical id for the object
     * @return  Unique id for the object
     */
    int getId() const;

protected:
    int id;     ///< Unique numerical id for the object

private:
    static int currId;  ///< Static variable that stores the number of objects created
};  //class UniqueId

}   //namespace Stoughton1004Lib
#endif
