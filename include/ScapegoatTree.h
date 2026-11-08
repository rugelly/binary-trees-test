#ifndef SCAPEGOATTREE_H_
#define SCAPEGOATTREE_H_

#include "../include/BinaryTree.h"
#include "../include/NodeScapegoat.h"

template <typename T, typename Node = NodeScapegoat<T>>
struct ScapegoatTree : BinaryTree<T, Node>
{
	int n; // number of nodes in tree
	int q; // upper bound for amount of nodes allowed in tree

	ScapegoatTree(); // constructor

	Node *insert(T data) override;
	Node *remove(Node *node) override;
};

#endif // SCAPEGOATTREE_H_
