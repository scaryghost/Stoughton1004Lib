#ifndef STOUGHTON1004LIB_BINARYHEAP_H
#define STOUGHTON1004LIB_BINARYHEAP_H

#include "Stoughton1004Lib/Heap/Heap.h"
#include <cstring>

namespace Stoughton1004Lib {

/**
 * Binary heap implementation of the Heap abstract class
 * @author etsai
 */
template <class T>
class BinaryHeap : public Heap<T> {
public:
    /**
     * Create a BinaryHeap, ordering the elements according to the custom comparator
     * @param   comparator  Custom comparator used to ordered the heap
     */
    BinaryHeap(const typename Heap<T>::Comparator& comparator);
    /**
     * Deallocate the used memory
     */
    virtual ~BinaryHeap();

    /**
     * Add an element to the head.  Operation is O(log n)
     * @param   elem    Element to add
     */
    virtual void add(const T& elem);
    /**
     * Remove the top of the heap.  Operation is O(log n)
     * @return  Top element of the heap
     */
    virtual T remove();
    /**
     * Merge the contents of the second heap into the calling object.  Operation is O(n)
     * @param   heap    Heap to merge with
     */
    virtual void merge(Heap<T> const *heap);

    virtual bool contains(const T& elem) const;
    virtual bool empty() const;
    /**
     * Retreive the top element.  Operation is O(1)
     * @return  Top element
     */
    virtual T top() const;
    virtual unsigned int size() const;
    /**
     * Print the contents of the heap.
     * This does not print the heap in sorted order, just in the order 
     * the elements reside in the list.
     * @param   os  Output stream to write to
     */
    virtual void print(std::ostream &os) const;
    /**
     * Print the contents of the heap with a newline.
     * This does not print the heap in sorted order, just in the order 
     * the elements reside in the list.
     * @param   os  Output stream to write to
     */
    virtual void println(std::ostream &os) const;
    virtual T get(int index) const;

private:
    T* elements;                    ///< Pointer to the allocated memory for the heap
    int numElements;                ///< Number of elements stored in the heap
    int capacity;                   ///< Max number of indices available

    static const int INIT_CAPACITY; ///< Initial capacity of the heap
};  //class BinaryHeap


template <class T>
const int BinaryHeap<T>::INIT_CAPACITY= 128;

template <class T>
BinaryHeap<T>::BinaryHeap(const typename Heap<T>::Comparator& comparator) : Heap<T>(comparator) {
    elements= new T[INIT_CAPACITY];
    numElements= 0;
    capacity= INIT_CAPACITY;
}

template <class T>
BinaryHeap<T>::~BinaryHeap() {
    delete[] elements;
    elements= nullptr;
}

template <class T>
void BinaryHeap<T>::add(const T& elem) {
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
T BinaryHeap<T>::remove() {
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
void BinaryHeap<T>::merge(Heap<T> const *heap) {
    unsigned int i;

    for(i= 0; i < heap->size(); i++) {
        add(heap->get(i));
    }
}

template <class T>
bool BinaryHeap<T>::contains(const T& elem) const {
    int index;
    for(index= 0; index < numElements && comparator(elements[index],elem) != 0; index++) {
    }

    return index < numElements;
}

template <class T>
bool BinaryHeap<T>::empty() const {
    return numElements == 0;
}

template <class T>
T BinaryHeap<T>::top() const {
    return elements[0];
}

template <class T>
unsigned int BinaryHeap<T>::size() const {
    return numElements;
}

template <class T>
void BinaryHeap<T>::print(std::ostream &os) const {
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
void BinaryHeap<T>::println(std::ostream &os) const {
    print(os);
    os << "\n";
}

template <class T>
T BinaryHeap<T>::get(int index) const {
    return elements[index];
}

}   //namespace Stoughton1004Lib

#endif  //STOUGHTON1004LIB_BINARYHEAP_H
