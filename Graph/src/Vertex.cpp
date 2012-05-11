#include "Stoughton1004Lib/Graph/Vertex.h"

#include <stdexcept>

namespace Stoughton1004Lib {

using std::runtime_error;

Vertex::Vertex() {
}
    
void Vertex::addEdge(const Edge& edge) {
    throw runtime_error("Not yet implemented!");
}

const std::vector<Edge>& Vertex::getEdges() const {
    throw runtime_error("Not yet implemented!");
}

std::string Vertex::getName() const {
    throw runtime_error("Not yet implemented!");
}

}
