#ifndef STOUGHTON1004LIB_HEAP_H
#define STOUGHTON1004LIB_HEAP_H

#include <functional>

namespace Stoughton1004Lib {

template <class T>

/**
 * Data structure implementing a heap, or priority queue.  Elements are ordered 
 * based on their natural ordering or by a Comparator.
 * @author etsai
 */
class Heap {
public:
    /** Type name for the comparator function type */
    typedef std::function<int (const T&, const T&)> Comparator;

    /**
     * Create a heap, ordered by the elements' natural ordering
     */
    Heap();
    /**
     * Create a heap, ordering the elements according to the custom comparator
     * @param   comparator  Custom comparator used to ordered the heap
     */
    Heap(const Comparator& comparator);
    /**
     * Copy constructor
     * @param   copy    Heap to copy from
     */
    Heap(const Heap& copy);
    /**
     * Deallocate the used memory
     */
    ~Heap();

    /**
     * Add an element to the head
     * @param   elem    Element to add
     */
    void add(const T& elem);
    /**
     * Remove the top of the heap
     * @return  Top element of the heap
     */
    T remove();

    /**
     * Checks if the element is present in the heap
     * @param   elem    Element to check
     * @return  True if the element is present
     */
    bool contains(const T& elem) const;
    /**
     * Checks if the heap is empty
     * @return  True if empty
     */
    bool empty() const;
    /**
     * Retreive the top element
     * @return  Top element
     */
    T top() const;
    /**
     * Retreive the number of elements in the heap
     * @return  Heap size
     */
    unsigned int size() const;

private:
    T* elements;                    ///< Pointer to the allocated memory for the heap
    int numElements;                ///< Number of elements stored in the heap
    int capacity;                   ///< Max number of indices available
    Comparator comparator;          ///< Custom comparator used for ordering
};  //class Heap

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_HEAP_H
