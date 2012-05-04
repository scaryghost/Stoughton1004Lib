#ifndef STOUGHTON1004LIB_GRAPH_H
#define STOUGHTON1004LIB_GRAPH_H

#include <tr1/unordered_map>
namespace Stoughton1004Lib {

/**
 * Represnts a collection of edges and vertices
 * @author etsai
 * @author sjiang
 */

class Vertex{
};

class Graph {
public:
  bool insertVertex(const Vertex & newVertex, const std::vector<Vertex> & newEdges);
	bool isConnected();
private:
	std::tr1::unordered_map<Vertex, std::vector<Vertex> > adjList;
};  //class Graph

}   //namespace Stoughton1004Lib

#endif
