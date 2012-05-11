#include "Stoughton1004Lib/Graph/Vertex.h"

#include <exception>

namespace Stoughton1004Lib {

using std::exception;

Vertex::Vertex() {
}
    
void Vertex::addEdge(const Edge& edge) {
    throw exception("Not yet implemented!");
}

const std::vector<Edge>& Vertex::getEdges() const {
    throw exception("Not yet implemented!");
}

std::string getName() const {
    throw exception("Not yet implemented!");
}

}
