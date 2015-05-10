#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>

using namespace std;

// Class that represents a single node in a linked list
class Node {
public:
	Node(int value) {
		_value = value;
		_next = NULL;
	}
	
	int getValue() const {
		return _value;
	}
	void setValue(int value) {
		_value = value;
	}
	
	Node* getNext() const {
		return _next;
	}
	void setNext(Node* next) {
		_next = next;
	}
	
private:
	int _value;
	Node *_next;
};

// Implementation of a singly linked list.
class LinkedList {
public:
	// Create a new empty linked list
	LinkedList();
	
	// Create a new linked list whose elements are copies of those in the
	// list "original". Insertions or deletions to the original list should
	// not affect the copied list, and insertions or deletions to the copied
	// list should not affect the original list.
	LinkedList(const LinkedList& original);

	// List destructor. Free the memory that's used by nodes in the list.
	~LinkedList();

	// Generate a string containing human-readable versions ofthe elements of
	// the list, with a space between pair of adjacent elements in the list.
	// For instance, if the list contains the elements [1, 2, 3] then the
	// output of this function should be "1 2 3" (without the quotes).
	string toString() const;

	// Create a new list whose elements are the same as those in the original
	// list, but which appear in the opposite order. For instance, if the
	// original list l contains the elements [1, 2, 3] then l.getReverse()
	// will return a new list which contains the elements [3, 2, 1].
	LinkedList* getReverse() const;

	// Insert a new node into the list. That node should have the value "value"
	// and should be located at position "offset". For instance, if offset = 0
	// then the node should be inserted into the list at the very beginning
	// of the list. If offset = 1 then the node should be inserted just after
	// what was previously the first element of the list. And so on.
	//
	// This function should return true if the element was successfully
	// inserted at the specified offset, and false otherwise.
	bool insert(int value, int offset);

	// Remove from the list every node whose value is equal to "value". This
	// function should return true if at least one element was erased from the
	// list, and false otherwise.
	bool erase(int value);

	// Get the number of elements in the list.
    int size() const;

	// Sort the elements in the list in ascending order
	void sort();

private:
	Node *_first; // A pointer to the first node in the list
	unsigned int _size; // The number of elements that are present in the list
};

#endif // LINKEDLIST_H_
