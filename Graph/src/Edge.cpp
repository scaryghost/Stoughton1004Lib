#include "Stoughton1004Lib/Graph/Edge.h"

#include <exception>

namespace Stoughton1004Lib {

using std::exception;

Edge::Edge() {
}

Edge::Edge(const Vertex start, const Vertex end) {
}

Edge& Edge::setAttribute(Attribute attr, float value) {
    throw exception("Not yet implemented!");
}

void Edge::connect(const T& start, const T& end) {
    throw exception("Not yet implemented!");
}

float Edge::getAttribute(Attribute attr) const {
    throw exception("Not yet implemented!");
}

Vertex& Edge::getStartVertex() const {
    throw exception("Not yet implemented!");
}

Vertex& Edge::getEndVertex() const {
    throw exception("Not yet implemented!");
}

std::string Edge::getName() const {
    throw exception("Not yet implemented!");
}

}
