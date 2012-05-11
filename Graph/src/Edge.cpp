#include "Stoughton1004Lib/Graph/Edge.h"

#include <stdexcept>

namespace Stoughton1004Lib {

using std::runtime_error;

Edge::Edge() {
}

Edge::Edge(const Vertex start, const Vertex end) {
}

Edge& Edge::setAttribute(Attribute attr, float value) {
    throw runtime_error("Not yet implemented!");
}

void Edge::connect(const Vertex& start, const Vertex& end) {
    throw runtime_error("Not yet implemented!");
}

float Edge::getAttribute(Attribute attr) const {
    throw runtime_error("Not yet implemented!");
}

Vertex& Edge::getStartVertex() const {
    throw runtime_error("Not yet implemented!");
}

Vertex& Edge::getEndVertex() const {
    throw runtime_error("Not yet implemented!");
}

std::string Edge::getName() const {
    throw runtime_error("Not yet implemented!");
}

}
