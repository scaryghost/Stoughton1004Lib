#ifndef STOUGHTON1004LIB_VERTEX_H
#define STOUGHTON1004LIB_VERTEX_H

#include <vector>

#include "Stoughton1004Lib/Graph/src/UniqueId.h"

namespace Stoughton1004Lib {

class Edge;

class Vertex : public UniqueId {
public:
    Vertex();
    
    void addEdge(const Edge& edge);
    const std::vector<Edge>& getEdges() const;

    std::string virtual getName() const
private:
    std::vector<Edge> edges;
};  //class Vertex

}   //namespace Stoughton1004Lib

#endif
