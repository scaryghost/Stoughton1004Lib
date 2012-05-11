#ifndef STOUGHTON1004LIB_EDGE_H
#define STOUGHTON1004LIB_EDGE_H

namespace Stoughton1004Lib {

/**
 * Stores information about an edge in a graph
 * @author etsai
 * @author sjiang
 */
template <class T>
class Edge {
public:
    /** Edge attributes */
    enum Attribute {
        WEIGHT  ///< Weight of the edge, used for shortest path, maximal flow, etc.
    };

    /** Default constructor */
    Edge();
    /**
     * Constructor with start and end vertices known
     * @param   start   Vertex the edge originates from
     * @param   end     Vertex the edge connects to
     */
    Edge(const T& start, const T& end);

    /**
     * Sets an edge attribute.
     * This setter uses the named parameter idiom, allowing chained 
     * calls on the same object
     * @param   attr    Edge attribute to set
     * @param   value   Value to set to
     * @return  Reference to the calling object
     */
    Edge& setAttribute(Attribute attr, float value);
    /**
     * Connects the edge between the given vertices
     * @param   start   Vertex the edge originates from
     * @param   end     Vertex the edge connects to
     */
    void connect(const T& start, const T& end);

    /**
     * Retrieve value for the given edge attribute
     * @param   attr    Attribute to poll
     * @return  Attribute value
     */
    float getAttribute(Attribute attr) const;
    /**
     * Get the vertex the edge originates from
     * @return  Reference to the origin vertex
     */
    T& getStartVertex() const;
    /**
    * Get the vertex the edge terminates at
    * @return Terminal vertex
    */
    T& getEndVertex() const;
};

}

#endif
