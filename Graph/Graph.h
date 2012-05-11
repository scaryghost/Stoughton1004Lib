#ifndef STOUGHTON1004LIB_GRAPH_H
#define STOUGHTON1004LIB_GRAPH_H

#include "Stoughton1004Lib/Graph/Edge.h"
#include "Stoughton1004Lib/Graph/Vertex.h"

#include <unordered_map>

namespace Stoughton1004Lib {

/**
 * Represnts a collection of edges and vertices
 * This class uses c++11 features supported in gcc 4.6.2.
 * @author etsai
 * @author sjiang
 */
class Graph {
public:
    bool insertVertex(const Vertex & newVertex, const std::vector<Vertex> & newEdges);
    bool isConnected();
private:
	std::unordered_map<int, Vertex> vertices;
    std::unordered_map<int, Edge> edges;
};  //class Graph

}   //namespace Stoughton1004Lib

#endif
