Doubly Linked List API in C
=====================

This is an implementation in C of the Doubly Linked List data structure.

A Doubly Linked List is a variation on the concept of a Singly Linked List.
A node in a Doubly Linked List is a data structure that contains three references or pointers. One points to the previous node in the list, one to the next node, and one points to the data contained in the node.

With each node pointing to the previous and next nodes in the list, the list can easily be traversed back and forth sequentially.
This type of data structure has an advantage over arrays in that they can grow and shrink as needed, whereas the length of an array in the classical sense must be known and declared ahead of time.

Nodes can also be inserted or deleted between two other nodes without having to shift data in other nodes around, as one would have to do inserting into an array.

One disadvantage is that, unlike an array, nodes cannot be accessed randomly with an index. To get to a specific node, one must traverse the entire list node by node until the desired node is found.

Compiled Files
================

Usage in Programs
=================
