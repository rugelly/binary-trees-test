#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "../include/Node.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

template <typename T, typename Node = Node<T>>
struct BinaryTree
{
	Node *root; // root node of tree

	BinaryTree();						// tree constructor
	BinaryTree(const BinaryTree &copy); // copy constructor

	int depth(Node *node);
	int size(Node *node);
	int height(Node *node);

	void preorder(Node *node); // recursively travels the left sub-tree, then the right. Starts from given root node
	void inorder(Node *node);
	void postorder(Node *node);

	// these perform their traversal until target node found.
	// Uses relevant helper funcs to find and return next node in traversal sequence (a.k.a. pre/in/postorder successor)
	Node *preorderNext(Node *node, T targetValue);
	Node *inorderNext(Node *node, T targetValue);
	Node *postorderNext(Node *node, T targetValue);

	virtual Node *insert(T data);	  // calls helper to perform insertion starting from tree root. Returns inserted node.
	virtual Node *remove(Node *node); // properly deletes node from tree. Returns nullptr if leaf removed, or node now in the removed nodes place.

	Node *find(T key); // calls helper to either return node with key, or print 'not found' msg

	bool verifyOrderProperty(Node *node); //  Calls recursive helper. Returns false if a node is found that does not meet BST sorting requirements.

	// SOURCE: almighty Push - with edit by Sarques
	// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c#51730733
	void print(); // displays binary tree in the console. Gets very W I D E very fast with each level of height.

	private:
	// helper funcs for printing (also from the stackoverflow link)
	void printlv(int n);
	void dispLV(Node *p, int lv, int d);

	bool verifyHelper(Node *node, T min, T max);			  // recursively checks that each node follows proper BST sorting.
	Node *copyHelper(Node *srcNode, Node *newParent);		  // recursive tree traversal to copy every node to a new Tree()
	Node *findHelper(Node *node, T key);					  // recursive func that traverses tree until Node with key = Node.data is found
	Node *findLeftmost(Node *node);							  // traverse left nodes until no more available. returns last found
	Node *insertHelper(Node *prev, Node *root, T data);		  // recursive function that follows BST rules for inserting data
	Node *removeSingleChildHelper(Node *node, Node *subtree); // re-usable logic for remove() when node only has one child

	// Helper funcs for pre/in/postorder successor finding.
	// Use the very specfic ruleset of each of their traversals
	Node *preorderRecurseBack(Node *node);
	Node *inorderRecurseDown(Node *node);
	Node *inorderRecurseBack(Node *node);
	Node *postorderRecurseDown(Node *node);
};

#endif // BINARYTREE_H_
