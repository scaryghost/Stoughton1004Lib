#ifndef STOUGHTON1004LIB_HEAP_H
#define STOUGHTON1004LIB_HEAP_H

#include <functional>

namespace Stoughton1004Lib {

template <class T>

/**
 * Data structure implementing a heap, or priority queue.  Elements are ordered 
 * based a Comparator.
 * @author etsai
 */
class Heap {
public:
    /** Type name for the comparator function type */
    typedef std::function<int (const T&, const T&)> Comparator;

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
    /**
     * Initialize the member variables.  Need this function because C++
     * does not support constructor delegation yet
     */
    void init();

    T* elements;                    ///< Pointer to the allocated memory for the heap
    int numElements;                ///< Number of elements stored in the heap
    int capacity;                   ///< Max number of indices available
    Comparator comparator;          ///< Custom comparator used for ordering

    static const int INIT_CAPACITY; ///< Initial capacity of the heap
};  //class Heap

template <class T>
const int Heap<T>::INIT_CAPACITY= 128;

template <class T>
Heap<T>::Heap(const Comparator& comparator) {
    init();
    this->comparator= comparator;
}

template <class T>
Heap<T>::Heap(const Heap& copy) {
    init();
    numElements= copy.numElements;
    capacity= copy.capacity;
    comparator= copy.comparator;
    useNaturalOrder= copy.useNaturalOrder;
    memcpy(elements, copy.elements, sizeof(T) * copy.capacity);
}

template <class T>
Heap<T>::~Heap() {
    delete[] elements;
    elements= NULL;
}

template <class T>
void Heap<T>::init() {
    elements= new T[INIT_CAPACITY];
    numElements= 0;
    capacity= INIT_CAPACITY;
}

template <class T>
void Heap<T>::add(const T& elem) {
    auto getParent= [](int index) -> { return (index-1)/2; };
    auto swap= [&this](int index1, int index2) -> void {
        T temp= elements[index1];
        elements[index1]= elements[index2];
        elements[index2]= elements[index1];
    };

    int parent, index= numElements;
    elements[numElements]= elem;
    
    parent= getParent(index);
    while(comparator(elements[parent], elements[index]) > 0) {
        swap(parent, index);
        index= parent;
        parent= getParent(index);
    }
    numElements++;
}

template <class T>
T Heap<T>::remove() {
    auto getLeftChild= [](int index) -> { return index * 2 + 1; };
    auto getRightChild= [](int index) -> { return (index + 1) * 2; };
    auto swap= [&this](int index1, int index2) -> void {
        T temp= elements[index1];
        elements[index1]= elements[index2];
        elements[index2]= elements[index1];
    };
    T top= elements[0];
    int index= 0;

    elements[index]= elements[numElements];
    numElements--;
    while(!(comparator(elements[index],elements[getLeftChild(index)]) > 0 && comparator(elements[index], elements[getRightChild(index)]) > 0)) {
        if (comparator(elements[index], elements[getLeftChild(index)] > 0)) {
            swap(index, getLeftChild(index));
            index= getLeftChild(index);
        } else if (comparator(elements[index], elements[getRightChild(index)]) > 0) {
            swap(index, getRightChild(index));
            index= getRightChild(index);
        }
        if (getLeftChild(index) >= numElements || getRightChild(index) >= numElements)
            break;
    }
    
}

template <class T>
bool contains(const T& elem) const {
    int index;
    for(index= 0; index < numElements && comparator(elements[index],elem) != 0; index++) {
    }

    return index < numElements;
}

template <class T>
bool empty() const {
    return numElements == 0;
}

template <class T>
T top() const {
    return elements[numElements];
}

template <class T>
unsigned int size() const {
    return numElements;
}

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_HEAP_H
