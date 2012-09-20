#ifndef STOUGHTON1004LIB_HEAP_H
#define STOUGHTON1004LIB_HEAP_H

#include <cstring>
#include <functional>
#include <ostream>

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
    /**
     * Print the contents of the heap in list index order.
     * This does not print the heap in sorted order, just in the order 
     * the elements reside in the list.
     * @param   os  Output stream to write to
     */
    void print(std::ostream &os) const;
    /**
     * Print the contents of the heap in list index order with an newline.
     * This does not print the heap in sorted order, just in the order 
     * the elements reside in the list.
     * @param   os  Output stream to write to
     */
    void println(std::ostream &os) const;

private:
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
    elements= new T[INIT_CAPACITY];
    numElements= 0;
    capacity= INIT_CAPACITY;
    this->comparator= comparator;
}

template <class T>
Heap<T>::Heap(const Heap& copy) {
    numElements= copy.numElements;
    capacity= copy.capacity;
    comparator= copy.comparator;
    elements= new T[capacity];
    std::memcpy(elements, copy.elements, sizeof(T) * copy.capacity);
}

template <class T>
Heap<T>::~Heap() {
    delete[] elements;
    elements= nullptr;
}

template <class T>
void Heap<T>::add(const T& elem) {
    auto getParent= [](int index) -> int { return (index-1)/2; };
    auto swap= [this](int index1, int index2) -> void {
        T temp= elements[index1];
        elements[index1]= elements[index2];
        elements[index2]= temp;
    };

    if (numElements == capacity) {
        T *newList= new T[numElements * 2];
        std::memcpy(newList, elements, sizeof(T) * capacity);
        delete[] elements;
        elements= newList;
        capacity*= 2;
    }

    int parent, index= numElements;
    elements[index]= elem;
    numElements++;

    parent= getParent(index);
    while(comparator(elements[parent], elements[index]) < 0) {
        swap(parent, index);
        index= parent;
        parent= getParent(index);
    }
}

template <class T>
T Heap<T>::remove() {
    auto getLeftChild= [](int index) -> int { return index * 2 + 1; };
    auto getRightChild= [](int index) -> int { return (index + 1) * 2; };
    auto swap= [this](int index1, int index2) -> void {
        T temp= elements[index1];
        elements[index1]= elements[index2];
        elements[index2]= temp;
    };
    T top= elements[0];
    int index= 0;

    elements[index]= elements[numElements-1];
    numElements--;
    while(!(comparator(elements[index],elements[getLeftChild(index)]) >= 0 
            && comparator(elements[index], elements[getRightChild(index)]) >= 0)) {

        if (comparator(elements[index], elements[getLeftChild(index)]) < 0 && 
            comparator(elements[index], elements[getRightChild(index)]) < 0) {
            if (comparator(elements[getLeftChild(index)], elements[getRightChild(index)]) > 0 ) {
                swap(index, getLeftChild(index));
                index= getLeftChild(index);
            } else {
                swap(index, getRightChild(index));
                index= getRightChild(index);
            }
        } else if (comparator(elements[index], elements[getLeftChild(index)]) < 0) {
            swap(index, getLeftChild(index));
            index= getLeftChild(index);
        } else if (comparator(elements[index], elements[getRightChild(index)]) < 0) {
            swap(index, getRightChild(index));
            index= getRightChild(index);
        }
        if (getLeftChild(index) >= numElements || getRightChild(index) >= numElements)
            break;
    }
    return top;
}

template <class T>
bool Heap<T>::contains(const T& elem) const {
    int index;
    for(index= 0; index < numElements && comparator(elements[index],elem) != 0; index++) {
    }

    return index < numElements;
}

template <class T>
bool Heap<T>::empty() const {
    return numElements == 0;
}

template <class T>
T Heap<T>::top() const {
    return elements[0];
}

template <class T>
unsigned int Heap<T>::size() const {
    return numElements;
}

template <class T>
void Heap<T>::print(std::ostream &os) const {
    os << "[";
    for(auto i= 0; i < numElements; i++) {
        if (i != 0) {
            os << ", ";
        }
        os << elements[i];
    }
    os << "]";
}

template <class T>
void Heap<T>::println(std::ostream &os) const {
    print(os);
    os << "\n";
}


}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_HEAP_H
