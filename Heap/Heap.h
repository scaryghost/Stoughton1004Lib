#ifndef STOUGHTON1004LIB_HEAP_H
#define STOUGHTON1004LIB_HEAP_H

#include <functional>
#include <ostream>

namespace Stoughton1004Lib {

template <class T>

/**
 * Abstract class defining common functions shared by all Heap implementations.
 * Elements are ordered based a Comparator and are arranged to form a max heap
 * @author etsai
 */
class Heap {
public:
    /**
     * Type name for the comparator function type.  The lambda returns 1 of 3 values: 
     * a number less than 0 if lhs < rhs, 0 if lhs == rhs, or a number greater than 0 
     * if lhs > rhs
     */
    typedef std::function<int (const T&, const T&)> Comparator;

    /**
     * Create a heap, ordering the elements according to the custom comparator
     * @param   comparator  Custom comparator used to ordered the heap
     */
    Heap(const Comparator& comparator);
    /**
     * Class destructor
     */
    virtual ~Heap();

    /**
     * Add an element to the head
     * @param   elem    Element to add
     */
    virtual void add(const T& elem)= 0;
    /**
     * Remove the top of the heap
     * @return  Top element of the heap
     */
    virtual T remove()= 0;
    /**
     * Merge the contents of the second heap into the calling object
     * @param   heap    Heap to merge with
     */
    virtual void merge(Heap<T> const *heap)= 0;

    /**
     * Checks if the element is present in the heap
     * @param   elem    Element to check
     * @return  True if the element is present
     */
    virtual bool contains(const T& elem) const= 0;
    /**
     * Checks if the heap is empty
     * @return  True if empty
     */
    virtual bool empty() const= 0;
    /**
     * Retreive the top element
     * @return  Top element
     */
    virtual T top() const= 0;
    /**
     * Retreive the number of elements in the heap
     * @return  Heap size
     */
    virtual unsigned int size() const= 0;
    /**
     * Print the contents of the heap.
     * @param   os  Output stream to write to
     */
    virtual void print(std::ostream &os) const= 0;
    /**
     * Print the contents of the heap with a newline.
     * @param   os  Output stream to write to
     */
    virtual void println(std::ostream &os) const= 0;
    /**
     * Retrieve the element stored at the index.
     * @param   index   Index to read from
     * @return  Element at the index
     */
    virtual T get(int index) const= 0;

protected:
    Comparator comparator;          ///< Custom comparator used for ordering
};  //class Heap

template <class T>
Heap<T>::Heap(const Comparator& comparator)
    :comparator(comparator) {
}

template <class T>
Heap<T>::~Heap() {
}

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_HEAP_H
