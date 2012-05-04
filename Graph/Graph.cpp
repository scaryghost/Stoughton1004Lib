#include "Graph.h"

bool Graph::insertVertex(const Vertex & newVertex, const std::vector<Vertex> & edges)
{
	return adjList.insert(std::pair<Vertex,std::vector<Vertex> >(newVertex, edges)).second;
}

bool Graph::isConnected()
{
}
