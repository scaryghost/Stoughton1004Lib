#ifndef STOUGHTON1004LIB_VERTEX_H
#define STOUGHTON1004LIB_VERTEX_H

#include <vector>

#include "Stoughton1004Lib/Graph/src/UniqueId.h"

namespace Stoughton1004Lib {

class Edge;

/**
 * Represents a vertex in a graph
 * @author etsai
 * @author sjiang
 */
class Vertex : public UniqueId {
public:
    /** Default constructor */
    Vertex();
    
    /**
     * Add an edge to the vertex
     * @param   edge    Edge to connect
     */
    void addEdge(const Edge& edge);
    /**
     * Get the edges originating from the vertex
     * @return  Vertex edges
     */
    const std::vector<Edge>& getEdges() const;

    std::string virtual getName() const
private:
    std::vector<Edge> edges;    ///< The edges originating from the vertex
};  //class Vertex

}   //namespace Stoughton1004Lib

#endif
