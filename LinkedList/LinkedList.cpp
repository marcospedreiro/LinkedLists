#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "LinkedList.h"


// Create a new empty linked list
LinkedList::LinkedList() {
	_first = NULL;
	_size = 0;
}

// Create a new linked list whose elements are copies of those in the
// list "original". Insertions or deletions to the original list should
// not affect the copied list, and insertions or deletions to the copied
// list should not affect the original list.
LinkedList::LinkedList(const LinkedList& original) {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::LinkedList(const LinkedList& original) is not yet ";
	std::cerr << "implemented" << std::endl;
	exit(1);*/
    
    Node *builder = new Node(original._first->getValue());
    Node *iter = builder;
    
    _first = builder;
    _size = 1;
    
    Node *traverser = original._first->getNext();
    
    while(traverser != NULL) {
        
        Node *newNode = new Node(traverser->getValue());
        iter->setNext(newNode);
        _size += 1;
        
        iter = iter->getNext();
        traverser = traverser->getNext();
    }
}

// List destructor. Free the memory that's used by nodes in the list.
LinkedList::~LinkedList() {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::~LinkedList() is not yet implemented" << std::endl;
	exit(1);*/
    
    Node* next = _first;
    
    while(_first != NULL) {
        next = _first->getNext();
        delete _first;
        _first = next;
    }
    delete next;
}

// Generate a string containing human-readable versions ofthe elements of
// the list, with a space between pair of adjacent elements in the list.
// For instance, if the list contains the elements [1, 2, 3] then the
// output of this function should be "1 2 3" (without the quotes).
std::string LinkedList::toString() const {
	std::ostringstream result;
	Node* traverser = _first;

	while (traverser != NULL) {
		result << traverser->getValue();
		
		if (traverser->getNext() != NULL) {
			result << " ";
		}
		traverser = traverser->getNext();
	}

	return result.str();
}

// Create a new list whose elements are the same as those in the original
// list, but which appear in the opposite order. For instance, if the
// original list l contains the elements [1, 2, 3] then l.getReverse()
// will return a new list which contains the elements [3, 2, 1].
LinkedList* LinkedList::getReverse() const {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::getReverse() is not yet implemented" << std::endl;
	exit(1);*/
    
    LinkedList *reversed = new LinkedList();
    Node *traverser = _first;
    
    while(traverser != NULL) {
        reversed->insert(traverser->getValue(), 0);
        traverser = traverser->getNext();
    }
    
    return reversed;
}

// Insert a new node into the list. That node should have the value "value"
// and should be located at position "offset". For instance, if offset = 0
// then the node should be inserted into the list at the very beginning
// of the list. If offset = 1 then the node should be inserted just after
// what was previously the first element of the list. And so on.
//
// This function should return true if the element was successfully
// inserted at the specified offset, and false otherwise.
bool LinkedList::insert(int value, int offset) {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::insert(value, offset) is not yet implemented" << std::endl;
	exit(1);*/
    
    if(offset > _size) {
        return false;
    }
    
    // handle offset 0
    if(offset == 0) {
        Node *newFirst = new Node(value);
        if(_first == NULL) {
            _first = newFirst;
        } else {
            newFirst->setNext(_first);
            _first = newFirst;
        }
        _size += 1;
        return true;
    }
    
    
    Node *traverser = _first;
    Node *prevTrav = traverser;
    
    while(traverser != NULL && offset != 0) {
        prevTrav = traverser;
        traverser = traverser->getNext();
        offset -= 1;
    }
    
    if(offset != 0) {
        return false;
    } else {
        // insert new node before traverser
        Node *nodeToInsert = new Node(value);
        
        // handle if inserting at end of list
        if(traverser == NULL) {
            prevTrav->setNext(nodeToInsert);
        } else {
            // handle previous node
            prevTrav->setNext(nodeToInsert);
            // handle traverser
            nodeToInsert->setNext(traverser);
        }
    }
    
    _size += 1;
    return true;
    
}

// Remove from the list every node whose value is equal to "value". This
// function should return true if at least one element was erased from the
// list, and false otherwise.
bool LinkedList::erase(int value) {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::erase(value) is not yet implemented" << std::endl;
	exit(1);*/
    
    bool didRemove = false; // init return bool as false
    Node* traverser = _first; // get head of list
    Node* prevNode = _first; // last non v node
    int index = 0; // init index as 0
    
    while(traverser != NULL) {
        Node* nextNode = traverser->getNext();
        if(index == 0) { // check head
            if(traverser->getValue() == value) { // head needs to be removed
                if(_size == 1) { // head is last element
                    delete traverser;
                    _first = NULL;
                    _size = 0;
                    traverser = nextNode;
                } else {
                    delete traverser;
                    if(nextNode->getValue() == value) { // next head needs to be removed
                        index = 0;
                    } else {
                        index = 1;
                    }
                    // increment
                    _first = nextNode;
                    traverser = nextNode;
                    prevNode = nextNode;
                    _size = _size - 1;
                    didRemove = true;
                }
            } else { // head does not need to be removed
                index = 1;
                prevNode = traverser;
                traverser = nextNode;
            }
        } else { // head is taken care of
            if(traverser->getValue() == value) { // normal case
                prevNode->setNext(nextNode);
                if(nextNode != NULL) { 
                    if(nextNode->getValue() != value) {
                        prevNode = nextNode;
                    }
                }
                delete traverser;
                traverser = nextNode;
                _size = _size - 1;
                didRemove = true;
            } else { // remove failed
                prevNode = traverser;
                traverser = nextNode;
            }
        }
    }
    
    return didRemove;
}

// Get the number of elements in the list.
int LinkedList::size() const {
	return _size;
}

// Sort the elements in the list in ascending order
void LinkedList::sort() {
	// TODO: Fill this in
	/*std::cerr << "LinkedList::sort() is not yet implemented" << std::endl;
	exit(1);*/
    
    vector<int> sortThis (_size);
    int sTIndex = 0;
    Node* traverser = _first;
    
    while(traverser != NULL) {
        sortThis[sTIndex] = traverser->getValue();
        traverser = traverser->getNext();
        sTIndex = sTIndex + 1;
    }
    
    std::sort(sortThis.begin(), sortThis.end());
    /* This is our implementation of selection sort that was learned
     in CS2110 */
    /*int n = _size;
    int minimumPosition;
    int temp;
    
    for (int i=0; i < n-1; i++) {
        
        minimumPosition = i;
        
        for (int k=i+1; k < n; k++) {
            if (sortThis[k] < sortThis[minimumPosition]) {
                minimumPosition = k;
            }
        }
        
        if (minimumPosition != i) {
            temp = sortThis[i];
            sortThis[i] = sortThis[minimumPosition];
            sortThis[minimumPosition] = temp;
        }
    }*/
    ///////////////////
    
    Node* traverserSorted = _first;
    int sortedIndex = 0;
    
    while(traverserSorted != NULL) {
        traverserSorted->setValue(sortThis[sortedIndex]);
        traverserSorted = traverserSorted->getNext();
        sortedIndex = sortedIndex + 1;
    }
    
    delete traverser;
    delete traverserSorted;
}






