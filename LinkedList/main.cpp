#include <iostream>

#include "LinkedList.h"
#include "DLinkedList.h"

using namespace std;

// This is a C++ precompiler macro that makes it easier to test whether the
// implementation of LinkedList is behaving as expected. If
// EXPECTED == ACTUAL then this macro does nothing. Otherwise,
// the macro prints an error message.
#define ASSERT_EQUAL(EXPECTED, ACTUAL) \
	if (EXPECTED != ACTUAL) { \
		cerr << __FILE__ << ":" << __LINE__ << ": "; \
		cerr << "Expected value \"" << EXPECTED << "\" does not match "; \
		cerr << "actual value \"" << ACTUAL << "\"" << endl; \
	}

// This macro does nothing if ACTUAL != NULL. However, if ACTUAL == NULL
// then it prints an error message.
#define ASSERT_NOT_NULL(ACTUAL) \
	if (ACTUAL == NULL) { \
		cerr << __FILE__ << ":" << __LINE__ << ": "; \
		cerr << "NULL pointer was passed to ASSERT_NOT_NULL" << endl; \
	}

void TestLL();
void TestDLL();

int main(int argc, const char **argv)
{
	cerr << "Testing LinkedList implementation..." << endl;
	TestLL();

	cerr << "Testing DLinkedList implementation..." << endl;
	TestDLL();

	cerr << "Passed all tests. Everything looks good to me!" << endl;
}

void TestLL() {
	cerr << "Create a new empty list" << endl;
	LinkedList list;
	ASSERT_EQUAL("", list.toString());

	cerr << "Add some new elements to the list" << endl;
	ASSERT_EQUAL(true, list.insert(1, 0));
	ASSERT_EQUAL(true, list.insert(2, 1));
	ASSERT_EQUAL(true, list.insert(3, 2));

	ASSERT_EQUAL("1 2 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	cerr << "Test out the copy constructor" << endl;
	LinkedList list2(list);
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	cerr << "Test out the list.getReverse() function" << endl;
	LinkedList *reversed = list.getReverse();
	ASSERT_NOT_NULL(reversed);
	ASSERT_EQUAL("3 2 1", reversed->toString());
	ASSERT_EQUAL(3, reversed->size());

	cerr << "Delete an element from the list" << endl;
	list.erase(2);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	cerr << "Try deleting an element that isn't present in the list" << endl;
	list.erase(42);
	ASSERT_EQUAL("1 3", list.toString());

	cerr << "Do some insertions" << endl;
	ASSERT_EQUAL(true, list.insert(0, 0));
	ASSERT_EQUAL("0 1 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	ASSERT_EQUAL(true, list.insert(0, 2));
	ASSERT_EQUAL("0 1 0 3", list.toString());
	ASSERT_EQUAL(4, list.size());

	cerr << "And now some deletions" << endl;
	list.erase(0);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	list.erase(1);
	ASSERT_EQUAL("3", list.toString());
	ASSERT_EQUAL(1, list.size());

	list.erase(3);
	ASSERT_EQUAL("", list.toString());
	ASSERT_EQUAL(0, list.size());

	cerr << "Make sure that reversed wasn't affected by the changes that were" << endl;
	cerr << "made to list" << endl;
	ASSERT_EQUAL("3 2 1", reversed->toString());

	// Make sure that "list2" wasn't affected by the changes that were
	// made to "list"
    cerr << "Testing Make sure that list2 wasn't affected by the changes that were made to list" << endl;
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());
    
	// Since list is a pointer, it will eating up memory until we manually
	// delete it. We don't use "reversed" after this point in the program,
	// so we need to tell the heap manager that we're done with it.
    //cerr << "Testing destructor" << endl;
	//delete reversed;
    
    // my tests
    cout << "List: " << list.toString() << endl;
    cout << "List2: " << list2.toString() << endl;
    cout << "Reversed: " << reversed->toString() << endl;
    ASSERT_EQUAL(true, list2.insert(99, 0));    //OUTPUT: 99,1,2,3
    ASSERT_EQUAL(false, list2.insert(58, 5));    //OUTPUT: test index out of bound
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,58,58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(-22, 4));    //OUTPUT: 58,58,58,99,-22,1,2,3
    ASSERT_EQUAL("58 58 58 99 -22 1 2 3", list2.toString());
    list2.sort();
    cout << "List2: " << list2.toString() << endl; //OUTPUT: -22,1,2,3,58,58,58,99
    //test reverse
    LinkedList *reversedTWO = list2.getReverse();
    ASSERT_NOT_NULL(reversed);
    cout << "reversedTWO: " << reversedTWO->toString() << endl; //OUTPUT: 99,58,58,58,3,2,1,-22
    //test erase
    cout << "List2: " << list2.toString() << endl; //OUTPUT:  -22,1,2,3,58,58,58,99
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,-22,1,2,3,58,58,58,99
    ASSERT_EQUAL(true, list2.insert(58, 9));    //OUTPUT: 58,-22,1,2,3,58,58,58,99,58
    cout << "List2: " << list2.toString() << endl; //OUTPUT:  58,-22,1,2,3,58,58,58,99,58
    list2.erase(58);
    cout << "List2: " << list2.toString() << endl; //OUTPUT: -22,1,2,3,99
    ASSERT_EQUAL(5, list2.size());
    //test copy list
    LinkedList list3(list2);
    ASSERT_EQUAL("-22 1 2 3 99", list3.toString());
    ASSERT_EQUAL(5, list3.size());
    
    delete reversedTWO;
    
}

void TestDLL() {
	cerr << "Create a new empty list" << endl;
	DLinkedList list;
	ASSERT_EQUAL("", list.toString());

	cerr << "Add some new elements to the list" << endl;
	ASSERT_EQUAL(true, list.insert(1, 0));
	ASSERT_EQUAL(true, list.insert(2, 1));
	ASSERT_EQUAL(true, list.insert(3, 2));

	ASSERT_EQUAL("1 2 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	cerr << "Test out the copy constructor" << endl;
	DLinkedList list2(list);
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	cerr << "Test out the list.getReverse() function" << endl;
	DLinkedList *reversed = list.getReverse();
	ASSERT_NOT_NULL(reversed);
	ASSERT_EQUAL("3 2 1", reversed->toString());
	ASSERT_EQUAL(3, reversed->size());

	cerr << "Delete an element from the list" << endl;
	list.erase(2);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	cerr << "Try deleting an element that isn't present in the list" << endl;
	list.erase(42);
	ASSERT_EQUAL("1 3", list.toString());

	cerr << "Do some insertions" << endl;
	ASSERT_EQUAL(true, list.insert(0, 0));
	ASSERT_EQUAL("0 1 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	ASSERT_EQUAL(true, list.insert(0, 2));
	ASSERT_EQUAL("0 1 0 3", list.toString());
	ASSERT_EQUAL(4, list.size());

	cerr << "And now some deletions, of 0" << endl;
	list.erase(0);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

    cerr << "Try deleting 1" << endl;
	list.erase(1);
	ASSERT_EQUAL("3", list.toString());
	ASSERT_EQUAL(1, list.size());

  	cerr << "Try deleting 3" << endl;
	list.erase(3);
	ASSERT_EQUAL("", list.toString());
	ASSERT_EQUAL(0, list.size());

    cerr << "Make sure that reversed wasn't affected by the changes that were" << endl;
    cerr << "made to list" << endl;
	ASSERT_EQUAL("3 2 1", reversed->toString());

	// Make sure that "list2" wasn't affected by the changes that were
	// made to "list"
    cerr << "Testing Make sure that list2 wasn't affected by the changes that were made to list" << endl;
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	// Since list is a pointer, it will eating up memory until we manually
	// delete it. We don't use "reversed" after this point in the program,
	// so we need to tell the heap manager that we're done with it.
    //cerr << "Testing destructor" << endl;
	//delete reversed;
    
    // my tests, repeat for Doubly Linked List
    cout << "List: " << list.toString() << endl;
    cout << "List2: " << list2.toString() << endl;
    cout << "Reversed: " << reversed->toString() << endl;
    ASSERT_EQUAL(true, list2.insert(99, 0));    //OUTPUT: 99,1,2,3
    ASSERT_EQUAL(false, list2.insert(58, 5));    //OUTPUT: test index out of bound
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,58,58,99,1,2,3
    ASSERT_EQUAL(true, list2.insert(-22, 4));    //OUTPUT: 58,58,58,99,-22,1,2,3
    ASSERT_EQUAL("58 58 58 99 -22 1 2 3", list2.toString());
    list2.sort();
    cout << "List2: " << list2.toString() << endl; //OUTPUT: -22,1,2,3,58,58,58,99
    //test reverse
    DLinkedList *reversedTWO = list2.getReverse();
    ASSERT_NOT_NULL(reversed);
    cout << "reversedTWO: " << reversedTWO->toString() << endl; //OUTPUT: 99,58,58,58,3,2,1,-22
    //test erase
    cout << "List2: " << list2.toString() << endl; //OUTPUT:  -22,1,2,3,58,58,58,99
    ASSERT_EQUAL(true, list2.insert(58, 0));    //OUTPUT: 58,-22,1,2,3,58,58,58,99
    ASSERT_EQUAL(true, list2.insert(58, 9));    //OUTPUT: 58,-22,1,2,3,58,58,58,99,58
    cout << "List2: " << list2.toString() << endl; //OUTPUT:  58,-22,1,2,3,58,58,58,99,58
    list2.erase(58);
    cout << "List2: " << list2.toString() << endl; //OUTPUT: -22,1,2,3,99
    ASSERT_EQUAL(5, list2.size());
    //test copy list
    DLinkedList list3(list2);
    ASSERT_EQUAL("-22 1 2 3 99", list3.toString());
    ASSERT_EQUAL(5, list3.size());
    
    delete reversedTWO;
}
        

        
        
        
        
