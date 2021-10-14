Red Black Tree API in C
=======================

This is an implementation in C of the Red Black Tree (RBT) data structure.

A Red Black Tree is a type of Binary Search Tree (BST) that has the additional capability of being self-balancing. In a regular BST, searching for, adding, or deleting a node can take, in the worst case, O(n) time (big O notation of time complexity). But in an RBT, by theoretically coloring each node either red or black, and maintaining a small set of rules as to how many red or black nodes can be next to each other, an RBT guarantees searching, inserting, and deleting in O(log n) time, even in the worst case.

[Red Black Tree on Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Terminology)

The API implemented here is designed to work within C programs compiled on Unix/Linux systems.

It is designed to be polymorphic, meaning that the tree can consist of nodes containing both built in C constructs, as well as custom user defined constructs. All that is required is that the user write a "compare function" for each new tree, that takes two void* data types as input, and returns an int type. The "compare function" must behave in the following way:

- If the first void* object is **"greater than"** the second void* object, function must return a **positive int**
- If the first object is **"less than"** the second, function must return a **negative int**
- If the objects are **"equal"** function must return **0**

The methods in the API will use each tree's compare function to find, insert and delete nodes to maintain a proper RBT.

The methods are also designed to use iterative loops, rather than recursive calls, to traverse the tree structure. This avoids the possible issue of a stack overflow altogether.

Compiled Files
===========

If the user has GNU make installed, using the make command within this directory will create the C library files rbt.o and rbtprint.o within a local lib/ directory. This will also create a few executables within a local bin/ directory, which I used for unit testing on the API.

**Library files:**

- **rbt.o:** Contains methods to create and perform operations on a Red Black Tree
- **rbtprint.o:** Contains a method rbtPrint that prints a text representation of an RBT to the console, to help visualize it

**Executables:**

- **rbtest:** Performs unit tests on the methods in rbt.o
- **rbtestprint:** Performs unit tests on the method in rbtprint.o
- **rbtplayer:** A program that allows the user to visualize the RBT by inserting and deleting integers

Usage in Programs
=======

- Any source file that uses the Red Black Tree API must include the rbt.h header.

   ```
   #include "rbt.h"
   ```

- The final compiled program must be linked with rbt.o

    ```
    gcc -c -o example.o example.c
    gcc -o example example.o rbt.o
    ```
