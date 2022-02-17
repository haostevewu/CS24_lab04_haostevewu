// intbst.cpp
// Implements class IntBST
// Hao Wu, 2022/02/03

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n) {
	printInOrder(n->left);
    cout << n->info << " ";
	printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {
	printPostOrder(n->left);
	printPostOrder(n->right);
    cout << n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    int sum1 = 0;
    if (n) {
	sum1 += sum(n->left);
	sum1 += sum(n->right);
    sum1 += n->info;
    }
    return sum1;
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    int count1 = 0;
    if (n) {
	count1 += count(n->left);
	count1 += count(n->right);
    count1 ++;
    }
    return count1;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    while (n) {
        if (n->info == value) {
            return n;
        } else {
            if (value > n->info) {
                n = n->right;
            } else {
                n = n->left;
            }
        }
    }
    return NULL;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* temp = getNodeFor(value,root);
    if (temp != NULL) {
        return true;
    }
    return false;
}

IntBST::Node* IntBST::findLeftMax(Node* n) const{
    n = n->left;
    while (n->right) {
        n = n->right;
    }
    return n;
}

IntBST::Node* IntBST::findLeftMin(Node* n) const{
    n = n->left;
    while (n->left) {
        n = n->left;
    }
    return n;
}

IntBST::Node* IntBST::findRightMin(Node* n) const{
    n = n->right;
    while (n->left) {
        n = n->left;
    }
    return n;
}

IntBST::Node* IntBST::findRightMax(Node* n) const{
    n = n->right;
    while (n->right) {
        n = n->right;
    }
    return n;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* temp = getNodeFor(value, root);
    if (temp && temp->left) {
        return findLeftMax(temp);
    } else {
        if (temp == findLeftMin(root)) {
            return temp;
        } else {
            while (temp->info >= value && temp != root) {
                temp = temp->parent;
            }
            return temp;
        }
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* temp = getPredecessorNode(value);
    if (temp && temp->info != value) {
        return temp->info;
    }
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* temp = getNodeFor(value, root);
    if (temp && temp->right) {
        return findRightMin(temp);
    } else {
        if (temp == findRightMax(root)) {
            return temp;
        } else {
            while (temp->info <= value && temp != root) {
                temp = temp->parent;
            }
            return temp;
        }
    }
    return temp;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* temp = getSuccessorNode(value);
    if (temp && temp->info != value) {
        return temp->info;
    }
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* temp = getNodeFor(value,root);
    if (temp && !temp->left && !temp->right) {
        if (temp == root) {
            root = nullptr;
            delete temp;
            return true;
        }
        if (temp == temp->parent->right) {
            temp->parent->right = nullptr;
        } else {
            temp->parent->left = nullptr;
        }
        delete temp;
        return true;
    }

    if (temp && !temp->left && temp->right) {
        if (temp == temp->parent->right) {
            temp->parent->right = temp->right;
            temp->right->parent = temp->parent;
        } else {
            temp->parent->left = temp->right;
            temp->right->parent = temp->parent;
        }
        delete temp;
        return true;
    }

    if (temp && temp->left && !temp->right) {
        if (temp == temp->parent->left) {
            temp->parent->right = temp->left;
            temp->left->parent = temp->parent;
        } else {
            temp->parent->left = temp->left;
            temp->left->parent = temp->parent;
        }
        delete temp;
        return true;
    }
    
    if (temp && temp->left && temp->right) {
        Node* suc = getSuccessorNode(value);
        int data = suc->info;
        remove(suc->info);
        temp->info = data;
        return true;
    }

    return false;
}
