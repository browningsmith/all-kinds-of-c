#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

#include "rbtimpl.h"

const char* rbtStatusAsText(RBTStatus status)
{
    const char* result;
    
    switch (status)
    {
        case SUCCESS:
            result = "SUCCESS";
            break;
        case NO_MEMORY:
            result = "NO_MEMORY";
            break;
        case NULL_CONTENT:
            result = "NULL_CONTENT";
            break;
        case EMPTY_NODE_ENCOUNTERED:
            result = "EMPTY_NODE_ENCOUNTERED";
            break;
        case NOT_FOUND:
            result = "NOT_FOUND";
            break;
    }

    return result;
}

void rbtInit(RBT* tree, int (*compareFunction) (void*, void*))
{
    // Initialize values
    tree->root = NULL;
    tree->compareFunction = compareFunction;
}

int rbtIsEmpty(RBT tree)
{
    if (tree.root == NULL)
    {
        return 1;
    }

    return 0;
}

RBTStatus rbtFind(RBT tree, void* query, void** returnedContent)
{
    // Check that query is not null
    if (query == NULL)
    {
        return NULL_CONTENT;
    }

    // If the tree is empty, return not found
    if (tree.root == NULL)
    {
        return NOT_FOUND;
    }

    // Perform search
    RBTStatusStruct result = rbtGetNodeFromStart__(tree.root, query, tree.compareFunction);

    if (result.status == SUCCESS)
    {
        *returnedContent = result.node->content;
        // result.status is SUCCESS
    }
    else if (result.status == NOT_FOUND)
    {
        // result.status is NOT_FOUND
    }
    else if (result.status == EMPTY_NODE_ENCOUNTERED)
    {
        // result.status is EMPTY_NODE_ENCOUNTERED
    }

    return result.status;
}

int rbtClear(RBT* tree, int (*clearingFunction) (void*))
{
    // If tree is empty, return success
    if (tree->root == NULL)
    {
        return 0;
    }
    
    int status = 0; // -1 means clearingFunction failed at some point
                    // -2 means the above, plus a tree containing
                    // undeleted data could not be constructed

    RBT undeletedNodes;
    rbtInit(&undeletedNodes, tree->compareFunction);

    // state 0 = recurse left
    // state 1 = recurse right
    // state 2 = delete this node and go up
    int state = 0;
    RBTNode* currentNode = tree->root;
    while (1)
    {
        if (state == 0)
        {
            // If left child is NULL, change to state 1
            if (currentNode->left == NULL)
            {
                state = 1;
                continue;
            }

            // Recurse left and remain at state 0
            currentNode = currentNode->left;
            continue;
        }

        if (state == 1)
        {
            // If right child is NULL, change to state 2
            if (currentNode->right == NULL)
            {
                state = 2;
                continue;
            }

            // Recurse right and change to state 0
            currentNode = currentNode->right;
            state = 0;
            continue;
        }

        if (state == 2)
        {
            RBTNode* parent = currentNode->parent;

            if (parent != NULL)
            {
                // If we are left child, set state to 1 before we go back up
                if (currentNode == parent->left)
                {
                    state = 1;
                }
                else // If we are right child, set state to 2 before we go back up
                {
                    state = 2;
                }
            }

            void* content = currentNode->content;
            free(currentNode);

            // Attempt to clear content using clearingFunction
            if (clearingFunction(content) != 0)
            {
                if (status > -1)
                {
                    status = -1;
                }

                // Attempt to insert content into undeletedNodes
                RBTStatus insertStatus = rbtInsert(&undeletedNodes, content);
                if (insertStatus != SUCCESS)
                {
                    status = -2;
                }
            }

            // If parent is NULL, we be done
            if (parent == NULL)
            {
                break;
            }

            // Go up to parent
            currentNode = parent;
            continue;
        }
    }
    
    // Set new root of tree to be the root of undeletedNodes
    tree->root = undeletedNodes.root;

    return status;
}

RBTStatus rbtInsert(RBT* tree, void* content)
{
    // Check that content is not null
    if (content == NULL)
    {
        return NULL_CONTENT;
    }

    // Create new node
    RBTNode* newNode = malloc(sizeof(RBTNode));
    if (newNode == NULL) // rbt returns NULL on error
    {
        return NO_MEMORY;
    }
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->content = content;

    // If tree is empty, insert new node as root and color it black, return SUCCESS and the new node
    if (tree->root == NULL)
    {
        tree->root = newNode;
        newNode->isRed = 0;

        return SUCCESS;
    }

    // Tree was not empty, color new node red
    newNode->isRed = 1;

    // Search for area to insert new node
    RBTNode* currentNode = tree->root;
    RBTStatusStruct result;

    while (
        ( result = rbtGetNodeFromStart__(
            currentNode,
            content,
            tree->compareFunction
        )).status != NOT_FOUND
    )
    {
        // EMPTY_NODE_ENCOUNTERED, free memory allocated for new node and return proper error
        if (result.status == EMPTY_NODE_ENCOUNTERED)
        {
            free(newNode);

            return result.status;
        }

        // SUCCESS means an equivalent node was found, attempt to insert to the right
        if (result.status == SUCCESS)
        {
            currentNode = result.node;

            // If right child is null, insert there
            if (currentNode->right == NULL)
            {
                currentNode->right = newNode;
                newNode->parent = currentNode;
                rbtFixRedViolations__(tree, newNode);

                return SUCCESS;
            }
            // Otherwise, recurse search for new place to insert
            else
            {
                currentNode = currentNode->right;
                continue;
            }
        }
    }

    // At this point, result.status is NOT_FOUND which means we can insert here

    // Compare newNode's content with content of current node
    currentNode = result.node;
    int compareResult = tree->compareFunction(content, currentNode->content);

    // If new node is less than current node, insert to the left
    if (compareResult < 0)
    {
        currentNode->left = newNode;
        newNode->parent = currentNode;
    }
    // If new node is greater than current node, insert to the right
    else
    {
        currentNode->right = newNode;
        newNode->parent = currentNode;
    }

    rbtFixRedViolations__(tree, newNode);

    return SUCCESS;
}

RBTStatus rbtDelete(RBT* tree, void* query, void** returnedContent)
{
    // Check that query is not null
    if (query == NULL)
    {
        return NULL_CONTENT;
    }

    // If the tree is empty, return not found
    if (tree->root == NULL)
    {
        return NOT_FOUND;
    }

    // Perform search
    RBTStatusStruct result = rbtGetNodeFromStart__(tree->root, query, tree->compareFunction);

    if (result.status == SUCCESS)
    {
        RBTNode* nodeToDelete = result.node;

        // Prepare returnedContent
        *returnedContent = nodeToDelete->content;

        // Begin deletion procedure

        // If node has two non NULL children
        if ((nodeToDelete->left != NULL) && (nodeToDelete->right != NULL))
        {
            RBTNode* replacement = rbtGetPrev__(nodeToDelete);
            nodeToDelete->content = replacement->content;
            nodeToDelete = replacement;
        }

        char nodeType; // h, l, or r
        RBTNode* parent = nodeToDelete->parent;

        if (nodeToDelete == tree->root)
        {
            nodeType = 'h';
        }
        else
        {
            if (nodeToDelete == parent->left)
            {
                nodeType = 'l';
            }
            else
            {
                nodeType = 'r';
            }
        }

        // If node is red, just delete
        if (nodeToDelete->isRed != 0)
        {
            if (nodeType == 'l')
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        // If node is black and left child exists
        else if (nodeToDelete->left != NULL)
        {
            nodeToDelete->left->isRed = 0;
            nodeToDelete->left->parent = parent;

            if (nodeType == 'l')
            {
                parent->left = nodeToDelete->left;
            }
            else if (nodeType == 'r')
            {
                parent->right = nodeToDelete->left;
            }
            else
            {
                tree->root = nodeToDelete->left;
            }
        }
        // If node is black and right child exists
        else if (nodeToDelete->right != NULL)
        {
            nodeToDelete->right->isRed = 0;
            nodeToDelete->right->parent = parent;

            if (nodeType == 'l')
            {
                parent->left = nodeToDelete->right;
            }
            else if (nodeType == 'r')
            {
                parent->right = nodeToDelete->right;
            }
            else
            {
                tree->root = nodeToDelete->right;
            }
        }
        // If node is black and has no children
        else
        {
            if (nodeType == 'h')
            {
                tree->root = NULL;
            }
            else
            {
                rbtFixBlackViolations__(tree, nodeToDelete);

                // Parent of nodeToDelete may have updated
                parent = nodeToDelete->parent;
                if (nodeToDelete == parent->left)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
        }

        free(nodeToDelete);
    }

    return result.status;
}

int rbtToRoot(RBTIterator* iterator, RBT* tree)
{
    if (tree->root == NULL)
    {
        return -1;
    }

    iterator->tree = tree;
    iterator->node = tree->root;

    return 0;
}

int rbtToStart(RBTIterator* iterator, RBT* tree)
{
    if (tree->root == NULL)
    {
        return -1;
    }

    iterator->tree = tree;

    RBTNode* node = tree->root;
    while (node->left != NULL)
    {
        node = node->left;
    }

    iterator->node = node;

    return 0;
}

// Implementation only definitions

RBTStatusStruct rbtGetNodeFromStart__(RBTNode* start, void* query, int (*compareFunction) (void* a, void* b))
{
    // Initialize result
    RBTStatusStruct result = { .node = NULL };

    RBTNode* currentNode = start;
    int compareResult;

    // Search algorithm
    while (1)
    {
        // Check that currentNode is not empty
        if (currentNode->content == NULL)
        {
            result.status = EMPTY_NODE_ENCOUNTERED;
            result.node = currentNode;
            break;
        }

        // Compare query with content of currentNode
        compareResult = compareFunction(query, currentNode->content);

        // If query matches currentNode's content, return SUCCESS and currentNode
        if (compareResult == 0)
        {
            result.status = SUCCESS;
            result.node = currentNode;
            break;
        }

        // If query is less than currentNode's content
        if (compareResult < 0)
        {
            // If currentNode's left child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->left == NULL)
            {
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                currentNode = currentNode->left;
                continue;
            }
        }

        // Here, query has to be greater than currentNode's content
        {
            // If currentNode's right child is NULL, search is over, return NOT_FOUND, and last node searched
            if (currentNode->right == NULL)
            {
                result.status = NOT_FOUND;
                result.node = currentNode;
                break;
            }
            else
            {
                currentNode = currentNode->right;
                continue;
            }
        }
    }

    return result;
}

void rbtRotateRight__(RBT* tree, RBTNode* leftChild)
{
    RBTNode* parent;
    RBTNode* grandParent;
    RBTNode* leftChildsRightChild;

    parent = leftChild->parent;
    grandParent = parent->parent;
    leftChildsRightChild = leftChild->right;

    // Set left child's parent to the grandParent
    leftChild->parent = grandParent;

    // If leftChild's parent is now NULL, leftChild is now the root
    if (leftChild->parent == NULL)
    {
        tree->root = leftChild;
    }
    else
    {
        // If parent was Grandparent's left child
        if (parent == grandParent->left)
        {
            grandParent->left = leftChild;
        }
        else // If parent was Grandparen't right child
        {
            grandParent->right = leftChild;
        }
    }

    // Left child's right becomes parent
    leftChild->right = parent;
    parent->parent = leftChild;

    // Parent's left becomes leftChildsRightChild
    parent->left = leftChildsRightChild;
    if (leftChildsRightChild != NULL)
    {
        leftChildsRightChild->parent = parent;
    }

    return;
}

void rbtRotateLeft__(RBT* tree, RBTNode* rightChild)
{
    RBTNode* parent;
    RBTNode* grandParent;
    RBTNode* rightChildsLeftChild;

    parent = rightChild->parent;
    grandParent = parent->parent;
    rightChildsLeftChild = rightChild->left;

    // Set right child's parent to the grandParent
    rightChild->parent = grandParent;

    // If rightChild's parent is now NULL, rightChild is now the root
    if (rightChild->parent == NULL)
    {
        tree->root = rightChild;
    }
    else
    {
        // If parent was Grandparent's right child
        if (parent == grandParent->right)
        {
            grandParent->right = rightChild;
        }
        else // If parent was Grandparen't left child
        {
            grandParent->left = rightChild;
        }
    }

    // Right child's left becomes parent
    rightChild->left = parent;
    parent->parent = rightChild;

    // Parent's right becomes rightChildsLeftChild
    parent->right = rightChildsLeftChild;
    if (rightChildsLeftChild != NULL)
    {
        rightChildsLeftChild->parent = parent;
    }

    return;
}

void rbtFixRedViolations__(RBT* tree, RBTNode* node)
{
    while (1)
    {
        RBTNode* parent;
        RBTNode* grandparent;
        RBTNode* uncle;

        int parentIsLeftChild;

        // If node is the root, color black and return
        if (node == tree->root)
        {
            node->isRed = 0;
            break;
        }

        parent = node->parent;

        // If parent is black, return
        if (parent->isRed == 0)
        {
            break;
        }

        // A node in red violation must have a grandparent
        grandparent = parent->parent;

        // Record what kind of child parent is, and get uncle
        if (parent == grandparent->left)
        {
            parentIsLeftChild = 1;
            uncle = grandparent->right;
        }
        else
        {
            parentIsLeftChild = 0;
            uncle = grandparent->left;
        }

        // If parent and uncle are both red, color them black and color grandparent red, recurse to grandparent
        if (uncle != NULL)
        {
            if (uncle->isRed != 0)
            {
                parent->isRed = 0;
                uncle->isRed = 0;
                grandparent->isRed = 1;
                node = grandparent;
                continue;
            }
        }

        // Parent is left child case
        if (parentIsLeftChild != 0)
        {
            if (node == parent->right)
            {
                rbtRotateLeft__(tree, node);
                parent = node;
            }

            parent->isRed = 0;
            grandparent->isRed = 1;
            rbtRotateRight__(tree, parent);
            break;
        }

        // Parent is right child case
        else
        {
            if (node == parent->left)
            {
                rbtRotateRight__(tree, node);
                parent = node;
            }

            parent->isRed = 0;
            grandparent->isRed = 1;
            rbtRotateLeft__(tree, parent);
            break;
        }
    }

    return;
}

void rbtFixBlackViolations__(RBT* tree, RBTNode* node)
{
    while (1)
    {
        // If violating node is the root, no violation, break
        if (node == tree->root)
        {
            break;
        }

        RBTNode* parent = node->parent;

        // Left case
        if (node == parent->left)
        {
            RBTNode* sibling = parent->right;
            RBTNode* leftNephew = sibling->left;
            RBTNode* rightNephew = sibling->right;

            int fixCase;
            // 1: black sibling with two black children
            // 2: black sibling with red right nephew
            // 3: black sibling with black right nephew
            // 4: red sibling

            if (sibling->isRed == 0)
            {
                int leftRed;
                int rightRed;

                if (leftNephew == NULL)
                {
                    leftRed = 0;
                }
                else if (leftNephew->isRed == 0)
                {
                    leftRed = 0;
                }
                else
                {
                    leftRed = 1;
                }

                if (rightNephew == NULL)
                {
                    rightRed = 0;
                }
                else if (rightNephew->isRed == 0)
                {
                    rightRed = 0;
                }
                else
                {
                    rightRed = 1;
                }

                if ((leftRed == 0) && (rightRed == 0))
                {
                    fixCase = 1;
                }
                else if (rightRed != 0)
                {
                    fixCase = 2;
                }
                else
                {
                    fixCase = 3;
                }
            }
            else
            {
                fixCase = 4;
            }

            switch (fixCase)
            {
                case 1:
                    
                    sibling->isRed = 1;

                    // If parent is red, color black and we're done
                    if (parent->isRed != 0)
                    {
                        parent->isRed = 0;
                        return;
                    }

                    // Else parent is now in violation, recurse to parent
                    node = parent;
                    
                    break;
                case 2:

                    // If parent is red
                    if (parent->isRed != 0)
                    {
                        parent->isRed = 0;
                        sibling->isRed = 1;
                    }
                    rightNephew->isRed = 0;
                    rbtRotateLeft__(tree, sibling);
                    return;

                    break;
                case 3:

                    // Color left nephew black, color sibling red, rotate nephew with sibling
                    leftNephew->isRed = 0;
                    sibling->isRed = 1;
                    rbtRotateRight__(tree, leftNephew);

                    break;
                case 4:
                    
                    // Color parent red, color sibling black, rotate sibling with parent
                    parent->isRed = 1;
                    sibling->isRed = 0;
                    rbtRotateLeft__(tree, sibling);
                    
                    break;
                default:
                    break;
            }
        }

        // Right case
        else
        {
            RBTNode* sibling = parent->left;
            RBTNode* leftNephew = sibling->left;
            RBTNode* rightNephew = sibling->right;

            int fixCase;
            // 1: black sibling with two black children
            // 2: black sibling with red left nephew
            // 3: black sibling with black left nephew
            // 4: red sibling

            if (sibling->isRed == 0)
            {
                int leftRed;
                int rightRed;

                if (leftNephew == NULL)
                {
                    leftRed = 0;
                }
                else if (leftNephew->isRed == 0)
                {
                    leftRed = 0;
                }
                else
                {
                    leftRed = 1;
                }

                if (rightNephew == NULL)
                {
                    rightRed = 0;
                }
                else if (rightNephew->isRed == 0)
                {
                    rightRed = 0;
                }
                else
                {
                    rightRed = 1;
                }

                if ((leftRed == 0) && (rightRed == 0))
                {
                    fixCase = 1;
                }
                else if (leftRed != 0)
                {
                    fixCase = 2;
                }
                else
                {
                    fixCase = 3;
                }
            }
            else
            {
                fixCase = 4;
            }

            switch (fixCase)
            {
                case 1:
                    
                    sibling->isRed = 1;

                    // If parent is red, color black and we're done
                    if (parent->isRed != 0)
                    {
                        parent->isRed = 0;
                        return;
                    }

                    // Else parent is now in violation, recurse to parent
                    node = parent;
                    
                    break;
                case 2:

                    // If parent is red
                    if (parent->isRed != 0)
                    {
                        parent->isRed = 0;
                        sibling->isRed = 1;
                    }
                    leftNephew->isRed = 0;
                    rbtRotateRight__(tree, sibling);
                    return;

                    break;
                case 3:

                    // Color right nephew black, color sibling red, rotate nephew with sibling
                    rightNephew->isRed = 0;
                    sibling->isRed = 1;
                    rbtRotateLeft__(tree, rightNephew);

                    break;
                case 4:
                    
                    // Color parent red, color sibling black, rotate sibling with parent
                    parent->isRed = 1;
                    sibling->isRed = 0;
                    rbtRotateRight__(tree, sibling);
                    
                    break;
                default:
                    break;
            }
        }
    }

    return;
}

RBTNode* rbtGetPrev__(RBTNode* node)
{
    // If left child exists
    if (node->left != NULL)
    {
        node = node->left;
        while (node->right != NULL)
        {
            node = node->right;
        }
    }

    // If left child does not exist
    else
    {
        while (1)
        {
            // If node is the root, no predecessor, return NULL
            if (node->parent == NULL)
            {
                return NULL;
            }

            // If node is left child
            if (node == node->parent->left)
            {
                node = node->parent;
                continue;
            }

            node = node->parent;
            break;
        }
    }

    return node;
}

RBTNode* rbtGetNext__(RBTNode* node)
{
    // If right child exists
    if (node->right != NULL)
    {
        node = node->right;
        while (node->left != NULL)
        {
            node = node->left;
        }
    }

    // If right child does not exist
    else
    {
        while (1)
        {
            // If node is the root, no predecessor, return NULL
            if (node->parent == NULL)
            {
                return NULL;
            }

            // If node is right child
            if (node == node->parent->right)
            {
                node = node->parent;
                continue;
            }

            node = node->parent;
            break;
        }
    }

    return node;
}