#include "Graph/src/UniqueId.h"

namespace Stoughton1004Lib {

int UniqueId::currId= 0;

int UniqueId::getCurrentId() {
    return currId;
}

UniqueId::UniqueId() {
    id= currId;
    currId++;
}

int Unique::getId() const {
    return id;
}

}   //namespace Stoughton1004Lib

