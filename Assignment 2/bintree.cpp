//
//  bintree.cpp
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

#include "bintree.h"
using namespace std;


/**
 * operator<< --------------------------------------------------------------------------------------------------------------------------------------
 * overloaded operator<< : Prints an inorder traversal of the tree
 * pre: none
 * post: prints the outputTree as an inorder traversal
 */

ostream& operator<<(ostream & out, const BinTree &outputTree) {
    outputTree.inorderHelper(outputTree.root);
    out << endl;
    return out;
}


/**
 * inorderHelper -----------------------------------------------------------------------------------------------------------------------------------
 * inorderHelper : helper for operator<< overloaded method by recursively moving through the BinTree
 * pre: none
 * post: prints the outputTree as an inorder traversal
 */
    
void BinTree::inorderHelper(Node* cur) const {
    if (cur != NULL) {             // base case
        inorderHelper(cur->left);
        cout << *cur->data << " "; // performs inorder traversal
        inorderHelper(cur->right);
    }
}
    

// Constructors //////////////////////////////////////////////////////////////


/**
 * BinTree -----------------------------------------------------------------------------------------------------------------------------------
 * Default Constructor : creates an empty BinTree and sets root to NULL
 */
    
BinTree::BinTree() {
    this->root = NULL;
}

    
/**
 * BinTree -------------------------------------------------------------------------------------------------------------------------------------------
 * Copy Constructor : creates a BinTree and creates a deep copy of the inputTree, setting it to this
 */

BinTree::BinTree(const BinTree &inputTree) {
    this->root = NULL;
    *this = inputTree;
}


/**
 * ~BinTree -----------------------------------------------------------------------------------------------------------------------------------------
 * Destructor : Deallocates all nodes of BinTree and sets root to NULL
 */

BinTree::~BinTree() {
    makeEmpty();
}

    
// Assignment Operators //////////////////////////////////////////////////////

/**
 * operator= ------------------------------------------------------------------------------------------------------------------------------------
 * overloaded =: true if this BinTree != parameter BinTree, false if not
 *
 * @param rhsTree : BinTree object to be copied
 * pre: none
 * post: Provides a deep copy of the parameter BinTree and sets to rhs of this
 * @return: this reference to new BinTree
 */
    
BinTree& BinTree::operator=(const BinTree &rhsTree) {
    if (*this != rhsTree) {         // avoid self-assignment
        makeEmpty();
        duplicateTree(this->root, rhsTree.root);
    }
    return *this;
}


/**
 * duplicateTree ------------------------------------------------------------------------------------------------------------------------------
 * duplicateTree : recursively copies nodes from rhs to lhs, duplicating entire tree
 *
 * @param lhs : Node to be replaced
 * @param rhs : Node to be copied
 * Pre: none
 * Post: Deep copies rhs Node to lhs
 */
    
void BinTree::duplicateTree(Node* &lhs, Node* rhs) {
    if (rhs == NULL) {                          // base case
        lhs = NULL;
    } else {
        lhs = new Node();                       // otherwise creates new node
        lhs->left = NULL;
        lhs->right = NULL;
        lhs->data = new NodeData(*rhs->data);   // provides deep copy
        
        duplicateTree(lhs->left, rhs->left);    // accounts for all child nodes
        duplicateTree(lhs->right, rhs->right);
    }
}

    
// Equality Operators ////////////////////////////////////////////////////
    

/**
 * operator== ------------------------------------------------------------------
 * overloaded ==: true if this BinTree == parameter BinTree, false if not
 *
 * @param rhsTree : BinTree object to be compared to this
 * pre: none
 * post: returns true if this BinTree == parameter BinTree
 * @return the value of equivalence
 */
    
bool BinTree::operator==(const BinTree& rhsTree) const {
    return equalityHelper(root, rhsTree.root);
}
    

/**
 * operator!= ------------------------------------------------------------------
 * overloaded !=: true if this BinTree != parameter BinTree, false if not
 *
 * @param rhsTree : BinTree object to be compared to this
 * pre: none
 * post:  returns true if this BinTree != parameter BinTree
 * @return the value of non-equivalence
 */
    
bool BinTree::operator!=(const BinTree& rhsTree) const {
    return !(equalityHelper(root, rhsTree.root));
}

    
/**
 * equalityHelper ----------------------------------------------------------------------------------------------------------------------------------
 * equalityHelper : recursively compares rhs nodes to lhs, throughout entire tree
 *
 * @param lhs : lhs Node to be compared
 * @param rhs : rhs Node to be compared
 * pre: none
 * post: returns false if any node from each tree is not equal, otherwise true
 * @return the value of equivalence
 */
    
bool BinTree::equalityHelper(Node* lhs, Node* rhs) const {
    if (lhs == NULL && rhs == NULL) {           // same value
        return true;
    } else if (lhs == NULL || rhs == NULL) {    // differing values
        return false;
    } else if (*lhs->data == *rhs->data) {      // same values, check children
        return (equalityHelper(lhs->left, rhs->left) &&
                equalityHelper(lhs->right, rhs->right));
    } else {                                    // differing values
        return false;
    }
}


    
// Mutators //////////////////////////////////////////////////////////////////////

/**
 * insert -------------------------------------------------------------------
 * insert : inserts a new Node containing the input newData into the BinTree object
 *
 * @param newData : the new newData object to be added to the tree
 * pre: newData object must be able to be comparable
 * post: inserts new Node struct containing newData, smaller to left, larger to the right
 * @return: the boolean value of success of insertion
 */
    
bool BinTree::insert(NodeData* newData) {
    return insertHelper(root, newData);
}

    
/**
 * insertHelper ----------------------------------------------------------------------------------------------------------------------------------
 * insertHelper : Helper function for insert. Recursively inserts a new Node containing the input newData
 * into the BinTree object
 *
 * @param cur : parent Node to be compared to newData
 * @param newData : the new newData object to be added to the tree
 * pre: newData object must be able to be comparable
 * post: inserts new Node struct containing newData, smaller to left, larger to the right, skips if already exists
 * @return: the boolean value of success of insertion
 */
    
bool BinTree::insertHelper(Node* &cur, NodeData* newData) {
    if (cur == NULL) {                              // base case to create new Node
        cur = new Node();
        cur->data = newData;
        cur->left = NULL;
        cur->right = NULL;
        return true;
    } else if (*newData < *cur->data) {             // BST, smaller goes left
        return insertHelper(cur->left, newData);
    } else if (*newData > *cur->data) {             // BST, larger goes right
        return insertHelper(cur->right, newData);
    } else {                                        // already exists, so skips
        return false;
    }
}


/**
 * makeEmpty ------------------------------------------------------------------------------------------------------------------------------
 * makeEmpty : deallocates all nodes of the BinTree object in this and sets root to NULL
 * pre: none
 * post: deallocates all nodes in memory and sets root to NULL
 */

void BinTree::makeEmpty() {
    makeEmptyHelper(root);
}
    
    
/**
 * makeEmptyHelper ----------------------------------------------------------------------------------------------------------------------------
 * makeEmptyHelper : helper function for makeEmpty. Deallocates all nodes of the BinTree object in this
 * and sets root to NULL
 *
 * @param cur : Node to be deleted
 * pre: none
 * post: deallocates all nodes in memory and sets root to NULL
 */

void BinTree::makeEmptyHelper(Node*& cur) {
    if (cur != NULL) {                      // can't deallocate if doesn't exist
        makeEmptyHelper(cur->left);         // account for children
        makeEmptyHelper(cur->right);
        delete cur->data;                   // deallocates NodeData and Node
        cur->data = NULL;
        delete cur;
        cur = NULL;
    }
}


// Accessors ////////////////////////////////////////////////////////////////////
    
/**
 * retrieve -------------------------------------------------------------------------------------------------------------------------------------------
 * retrieve : returns the bool value of whether data desired is in this tree, modifying the dataRetrieved directly
 * to be NodeData object, if found
 *
 * @param dataDesired : pass-by-reference newData object to be searched for in tree
 * @param dataRetrieved : newData object to point to object in tree, if found
 * pre: newData object must be able to be comparable
 * post: if found, returns true and dataRetrieved points to object in tree
 * @return: the boolean value whether object is found
 */
    
bool BinTree::retrieve(const NodeData &dataDesired, NodeData* &dataRetrieved) {
    return retrieveHelper(this->root, dataDesired, dataRetrieved);
}
    

/**
 * retrieveHelper -------------------------------------------------------------------------------------------------------------------------------------
 * retrieveHelper : recursive helper function for retrieve function. Returns the
 * bool value of whether data desired is in this tree,modifying the dataRetrieved directly to be NodeData object, if found
 *
 * @param dataDesired : pass-by-reference newData object to be searched for in tree
 * @param dataRetrieved : newData object to point to object in tree, if found
 * pre: newData object must be able to be comparable
 * post: if found, returns true and dataRetrieved points to object in tree
 * @return: the boolean value whether object is found
 */

bool BinTree::retrieveHelper(Node* &cur, const NodeData &dataDesired, NodeData* &dataRetrieved) const {
    if (cur == NULL) {                          // Base case, NodeData not in tree
        dataRetrieved = NULL;
        return false;
    } else if (dataDesired == *cur->data) {     // 2nd Base, NodeData found
        dataRetrieved = cur->data;
        return true;
    } else if (dataDesired < *cur->data) {      // dataDesired smaller, check left
        return retrieveHelper(cur->left, dataDesired, dataRetrieved);
    } else {                                    // dataDesired larger, check right
        return retrieveHelper(cur->right, dataDesired, dataRetrieved);
    }
}


/**
 * getHeight ---------------------------------------------------------------------------------------------------------------------------------
 * getHeight : returns the height of a general tree of a given value.
 * The height of a leaf node is 1, and a value not found is zero.
 *
 * @param dataDesired : pass-by-reference newData object to be searched for in tree
 * pre: none
 * post: if found, returns height of tree from node with found value.
 * @return: the height of the tree at the given node, 1 if leaf, 0 if not found
 */

int BinTree::getHeight (const NodeData &dataDesired) const {
    return getHeightHelper(root, dataDesired);
}


/**
 * getHeightHelper ---------------------------------------------------------------
 * getHeightHelper : recurisve helper function for getHeight. Returns the height of a general tree of a given value.
 * Height of a leaf node is 1, and a value not found is 0.
 *
 * @param cur : current Node to be searched for dataDesired
 * @param dataDesired : pass-by-reference newData object to be searched for in tree
 * pre: none
 * post: if found, calls overloaded height function to find height at cur
 * @return the height of the tree at the given node, 1 if leaf, 0 if not found
 */
    
int BinTree::getHeightHelper (Node* cur, const NodeData &dataDesired) const {
    if (cur == NULL) {                          // Base case; doesn't exist is 0
        return 0;
    } else if (*cur->data == dataDesired) {     // calls overloaded getHeight
        return getHeight(cur);
    } else {                                    // Continues searching
        return max(getHeightHelper(cur->left, dataDesired), // returns largest height
                   getHeightHelper(cur->right, dataDesired));
    }
}
    

/**
 * getHeight -------------------------------------------------------------------
 * getHeight : overloaded getHeight recursively returns the height of a general tree of the given node.
 * The height of a leaf node is 1, and cur == NULL returns zero.
 *
 * @param cur : current Node of which to determine height
 * pre: none
 * post: returns height of tree from given node
 * @return: the height of the tree at the given node, 1 if leaf, 0 if NULL
 */

int BinTree::getHeight (Node* cur) const {
    if (cur == NULL) {                       // Base case, doesn't exist is 0
        return 0;
    } else {                                 // Leaf nodes add 1, plus max height
        return 1 + max(getHeight(cur->left), getHeight(cur->right));
    }
}


// Using Arrays ////////////////////////////////////////////////////////////////////

/**
 *  bstreeToArray  --------------------------------------------------------------------------------------------------------------------------------
 *  bstreeToArray :  function to fill an array of NodeData using an inorder traversal of the tree. it leaves the tree empty,
 *  and the NodeData array passted in a statically-located array of 100 NULL elements.
 *
 *  @param newArray : array to be filled with inorder traversal of NodeData elements from tree
 *  pre: NodeData array must be a statically-located array of 100 NULL elements
 *  post: tree will be deallocated and newArray filled with NodeData elements from tree in inorder traversal
 */

void BinTree::bstreeToArray(NodeData* newArray[]) {
    int index = 0;              // helper veriable to determine position in array
    bstreeToArrayHelper(newArray, root, index);
    makeEmpty();                // clear tree
}


/**
*  bstreeToArrayHelper  --------------------------------------------------------------------------------------------------------------------------------
*  bstreeToArrayHelper : recursive helper function to bstToArray  to fill an array of NodeData using an inorder traversal of
*  the tree. it leaves the tree empty,and the NodeData array passted in a statically-located array of 100 NULL elements.
*
* @param newArray : array to be filled with inorder traversal of NodeData elements from tree
* @param cur : current Node to access NodeData
* @param index : helper reference variable to keep track of position in array while being filled
*  pre: NodeData array must be a statically-located array of 100 elements
*  post: tree will be deallocated and newArray filled with NodeData elements from tree in inorder traversal
*/

void BinTree::bstreeToArrayHelper(NodeData* newArray[], Node* cur, int& index) {
    if (cur != NULL) {                              // Only copy actual Nodes
        bstreeToArrayHelper(newArray, cur->left, index); // inorder traversal
        newArray[index] = new NodeData(*cur->data); // Deep copy of NodeData
        index++;                                    // Next position in array
        bstreeToArrayHelper(newArray, cur->right, index); // continue traversal
    }
}


/**
*  arraytoBSTree --------------------------------------------------------------------------------------------------------------------------------
*  arraytoBSTree :  function to build a balanced BinTree from a sorted array of NodeData* elements, leaving the
*  array filled with NULLS.
*
*  @param oldArray : 100-element NodeData array to be used to build BinTree. Elements taken will be replaced with NULL
*  pre: NodeData array must be a statically-located array of size 100
*  post: this will be emptied and replaced with a balanced BinTree made of elements from oldArray,
*  which will be filled with NULLs
*/

void BinTree::arrayToBSTree(NodeData* oldArray[]) {
    int low = 0; int high = 0;          // creates bounds of array to be searched
    for (int i = 0; i < 100; i++) {     // find highest index of NodeData in array
        if (oldArray[i] != NULL) {
            high++;
        }
    }
    makeEmpty();
    arrayToBSTreeHelper(oldArray, low, high - 1);
}


/**
*  arraytoBSTreeHelper --------------------------------------------------------------------------------------------------------------------------------
*  arraytoBSTreeHelper : recursive helpr function for arrayToBSTree, to  build a balanced BinTree from a sorted array of
*  NodeData* elements, leaving the array filled with NULLS.
*
*  @param oldArray : 100-element NodeData array to be used to build BinTree. Elements taken will be replaced with NULL
* @param low : lowest subscript of the array range
* @param high : highest subscript of the array range
*  pre: NodeData array must be a statically-located array of size 100
*  post: elements from oldArray will be used to create a balanced BinTree, and afterward will be filled with NULLs
*/

void BinTree::arrayToBSTreeHelper(NodeData* oldArray[], int low, int high) {
    if (high >= low) {
        int midIndex = (low + high) / 2;
        NodeData* newNode = oldArray[midIndex];
        insert(newNode);
        oldArray[midIndex] = NULL;
        arrayToBSTreeHelper(oldArray, low, midIndex - 1);
        arrayToBSTreeHelper(oldArray, midIndex + 1, high);
    }
}


/**
 * displaySideways ------------------------------------------------------------------------------------------------------------------------
 * Displays a binary tree as though you are viewing it from the side; hard coded displaying to standard output.
 * Preconditions: NONE
 * Postconditions: BinTree remains unchanged.
 */

void BinTree::displaySideways() const {
    sideways(root, 0);
}

/**
 * Sideways ----------------------------------------------------------------------------------------------------------------------------
 * Helper method for displaySideways
 * Preconditions: NONE
 * Postconditions: BinTree remains unchanged.
 * @param current : current Node to be output
 * @param level : accounting for space at current depth level
 */

void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}

// Helpers

/**
 * isEmpty ----------------------------------------------------------------------------------------------------------------------------------
 * Function to determine if BinTree is empty or not, returning the bool value of emptiness
 * Pre: none
 * Post: returns true if BinTree is empty, meaning it contains no Node objects, false if not
 */
bool BinTree::isEmpty() const {
    if (root == NULL) {
        return true;
    }
    return false;
}
