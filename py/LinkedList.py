#!/usr/bin/env python

from threading import Lock


class LinkedList:
    def __init__(self, value=None):
        self.first = Node(value)
        self.size = 1
        self.lock = Lock()
    
    # Creates a new node with value 'value' and inserts it into the list
    # at position 'pos'. pos = 0 inserts at the head of list
    # Returns true if successful, false otherwise
    def insert(self, value, pos):
        with self.lock:
            if pos == 0:
                new_node = Node(value, self.first)
                self.first = new_node
                self.size += 1
                return True
            else:
                new_node = Node(value)
                traverse = self.first
                prev_node = self.first
                while traverse is not None and pos > 0:
                    prev_node = traverse
                    traverse = traverse.get_next()
                    pos -= 1
                    
                if prev_node is not None and pos == 0:  # found correct position
                    prev_node.set_next(new_node)
                    new_node.set_next(traverse)
                    self.size += 1
                    return True
            return False
    
    # Deletes the first node that has a value of 'value'
    # returns true if successful, false otherwise
    def erase(self, value):
        with self.lock:
            if self.first.getvalue() == value:  # delete head
                temp = self.first
                self.first = self.first.get_next()
                del temp
                self.size -= 1
                return True
            else:
                traverse = self.first
                prev_node = self.first
                while traverse is not None:
                    if traverse.getvalue() == value:  # found value to delete
                        next_node = traverse.get_next()
                        prev_node.set_next(next_node)
                        del traverse
                        self.size -= 1
                        return True
                    prev_node = traverse
                    traverse = traverse.get_next()
            return False
    
    # Removes None values from LL, worst case O(n^2) run time
    # List must be populated with at least 1 non None element
    def clear_nones(self):
        with self.lock:
            traverse = self.first
            while traverse is not None:
                if traverse.getvalue() is not None:
                    self.erase(None)
                traverse = traverse.get_next()
    
    # Searches the linked list for the first instance of 'value'
    # Returns the node if found, does nothing otherwise
    def search(self, value):
        with self.lock:
            traverse = self.first
            while traverse is not None:
                if traverse.getvalue() == value:
                    return traverse
                traverse = traverse.get_next()
            return
    
    # Returns a new linked list with the elements in reverse order
    def reverse(self):
        with self.lock:
            rev_list = LinkedList(self.first.getvalue())
            traverse = self.first.get_next()
            while traverse is not None:
                rev_list.insert(traverse.getvalue(), 0)
                traverse = traverse.get_next()
            return rev_list
    
    # Returns the linked list as a string in the format
    # '[e1, e2, ..., en]'
    def tostring(self):
        with self.lock:
            if self.first is None:
                as_string = '[]'
            else:
                traverse = self.first
                as_string = '['
                while traverse is not None:
                    val = traverse.getvalue()
                    if traverse.get_next() is None:
                        as_string = as_string + str(val) + ']'
                    else:
                        as_string = as_string + str(val) + ', '
                    traverse = traverse.get_next()
            return as_string
    
    # Returns the size (length) of the linked list
    def getsize(self):
        with self.lock:
            return self.size
    
    # transforms the linked list into a normal python list, returns the list
    def tolist(self):
        with self.lock:
            traverse = self.first
            as_list = []
            while traverse is not None:
                as_list.append(traverse.getvalue())
                traverse = traverse.get_next()
            return as_list
    
    # inserts values into a linked list from a given list
    def fromlist(self, input_list):
        with self.lock:
            index = 0
            for i in input_list:
                self.insert(i, index)
                index += 1
            return
    
    
#################################################################
# Class defining the node structure to be used in the Linked List
class Node:
    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next_node = next_node

    def getvalue(self):
        return self.value

    def set_value(self, value):
        self.value = value

    def get_next(self):
        return self.next_node
        
    def set_next(self, next_node):
        self.next_node = next_node