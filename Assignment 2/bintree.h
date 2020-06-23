//
//  bintree.h
//
//  Created by Josiah Zacharias on 1/19/2020.
//  Last modified on 2/1/2020
//
//  BinTree Object: creates binary search tree by reading in a data file
//  consisting of many lines, of which each are a string that terminates
//  with the string "$$". Each line will be used to build one tree, filling
//  the data values with NodeData objects. Smaller strings go left, and bigger
//  go right.
//
//  Assumptions:
//     -- Input assumed to be correct and consist of NodeData objects, to be
//        implemented by client
//     -- BSTs and arrays produced are assumed to be no more than 100 nodes,
//        and any index not referencing a BinTree node should be NULL

#ifndef BINTREE_H
#define BINTREE_H
#include <stdio.h>
#include "nodedata.h"
using namespace std;

class BinTree {

    // operator<< -------------------------------------------------------
    // Prints an inorder traversal of the tree
    friend ostream& operator<<(ostream &out, const BinTree &);
    
public:
    // Constructor/Destructor //////////////////////////////////////////////
    
    // BinTree ---------------------------------------------------------
    // Default Constructor : creates an empty BinTree and sets root to NULL
    BinTree();
    
    // BinTree ----------------------------------------------------------
    // Copy Constructor : creates a BinTree and creates a deep copy of the
    // inputTree, setting it to this
    BinTree(const BinTree &);
    
    // ~BinTree ----------------------------------------------------------
    // Destructor : Deallocates all nodes of BinTree and sets root to NULL
    ~BinTree();
    
    
    // Assignment Operators ////////////////////////////////////////////////
    
    // operator= --------------------------------------------------------
    // overloaded =: true if this BinTree != parameter BinTree, false if not
    BinTree& operator=(const BinTree &);
    
    
    // Equality Operators //////////////////////////////////////////////////
    
    // operator== ---------------------------------------------------------
    // overloaded ==: true if this BinTree == parameter BinTree, false if not
    bool operator==(const BinTree &) const;
    
    // operator!= ---------------------------------------------------------
    // overloaded !=: true if this BinTree != parameter BinTree, false if not
    bool operator!=(const BinTree &) const;
    
    // Mutators ////////////////////////////////////////////////////////////
    
    // insert ---------------------------------------------------------------
    // inserts a new Node containing the input newData into the BinTree object
    bool insert(NodeData*);
    
    // makeEmpty ------------------------------------------------------------
    // deallocates all nodes of the BinTree object in this and sets root to NULL
    void makeEmpty();

    
    // Accessors ///////////////////////////////////////////////////////////
    
    // retrieve ------------------------------------------------------------
    // returns the bool value of whether data desired is in this tree, modifying
    // the dataRetrieved directly to be NodeData object, if found
    bool retrieve(const NodeData &, NodeData* &);
    
    // getHeight ------------------------------------------------------------
    // returns the height of a general tree of a given value.
    int getHeight (const NodeData &) const;

    // isEmpty ---------------------------------------------------------------
    // true if tree is empty, otherwise
    bool isEmpty() const;
    
    
    // Output Functions /////////////////////////////////////////////////////
    
    // displaySideways -----------------------------------------------------
    // Displays a binary tree as though you are viewing it from the side;
    // hard coded displaying to standard output.
    void displaySideways() const;
    
    // bstreeToArray  -------------------------------------------------------
    // function to fill an array of NodeData using an inorder traversal of the
    // tree. it leaves the tree empty, and the NodeData array passted in a
    // statically-located array of 100 NULL elements.
    void bstreeToArray(NodeData* []);
    
    // arraytoBSTree -----------------------------------------------------
    // function to build a balanced BinTree from a sorted array of NodeData*
    // elements, leaving the array filled with NULLS.
    void arrayToBSTree(NodeData* []);
    
private:
    
    // Custom structure for Nodes to be used in BinTree
    struct Node {
        NodeData* data;                        // pointer to data object
        Node* left;                            // left subtree pointer
        Node* right;                           // right subtree pointer
    };
    Node* root;                                // root of the tree

    
    // Utility functions //////////////////////////////////////////////
        
    // inorderHelper -----------------------------------------------------
    // helper for operator<< overloaded method by recursively moving through the BinTree
    void inorderHelper(Node*) const;
    
    // Sideways -----------------------------------------------------------
    // Helper method for displaySideways
    void sideways(Node*, int) const;
    
    // makeEmptyHelper ----------------------------------------------------
    // helper function for makeEmpty. Deallocates all nodes of the BinTree
    void makeEmptyHelper(Node* &);
    
    // duplicateTree -------------------------------------------------------
    // recursively copies nodes from rhs to lhs, duplicating entire tree
    void duplicateTree(Node* &, Node*);
    
    // equalityHelper -----------------------------------------------------
    // recursively compares rhs nodes to lhs, throughout entire tree
    bool equalityHelper(Node*, Node*) const;
    
    // insertHelper ---------------------------------------------------------
    // Helper function for insert. Recursively inserts a new Node containing
    // the input newData
    bool insertHelper(Node* &, NodeData*);
    
    // retrieveHelper -------------------------------------------------------
    // recursive helper function for retrieve function. Returns the bool value
    // of whether data desired is in this tree,modifying the dataRetrieved
    // directly to be NodeData object, if found
    bool retrieveHelper(Node* &, const NodeData &, NodeData* &) const;
    
    // getHeightHelper ----------------------------------------------------
    // recurisve helper function for getHeight. Returns the height of a
    // general tree of a given value. Height of a leaf node is 1, and a value
    // not found is 0.
    int getHeightHelper (Node*, const NodeData &) const;
    
    // getHeight ----------------------------------------------------------
    // overloaded getHeight recursively returns the height of a general tree
    // of the given node. The height of a leaf node is 1, and cur == NULL
    // returns zero.
    int getHeight (Node*) const;
    
    // bstreeToArrayHelper  ------------------------------------------------
    // recursive helper function to bstToArray  to fill an array of NodeData
    // using an inorder traversal of the tree. it leaves the tree empty,
    // and the NodeData array passted in a statically-located array of 100
    // NULL elements.
    void bstreeToArrayHelper(NodeData* [], Node*, int&);
    
    // arraytoBSTreeHelper -------------------------------------------------
    // recursive helpr function for arrayToBSTree, to  build a balanced BinTree
    // from a sorted array of NodeData* elements, leaving the array
    // filled with NULLS.
    void arrayToBSTreeHelper(NodeData* [], int, int);
        
};

#endif
