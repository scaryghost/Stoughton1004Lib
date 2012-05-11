#ifndef STOUGHTON1004LIB_VERTEX_H
#define STOUGHTON1004LIB_VERTEX_H

#include <vector>

namespace Stoughton1004Lib {

class Edge;

class Vertex {
public:
    static int numVertices;

    Vertex();
    
    void addEdge(const Edge& edge);
    const std::vector<Edge>& getEdges() const;
    int getId() const;

private:
    int id;
    std::vector<Edge> edges;
};

}  //namespace Stoughton1004Lib

#endif
