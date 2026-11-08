#include "../include/ScapegoatTree.h"

template <typename T, typename Node>
ScapegoatTree<T, Node>::ScapegoatTree()
{
	this->root = nullptr;
}

template <typename T, typename Node>
Node *ScapegoatTree<T, Node>::insert(T data)
{
	n++;
	q++;

	Node *inserted = BinaryTree<T, Node>::insert(data); // base impl.
	Node *traversal = inserted;
	int depth = 0;

	// traverse parents until nullptr: root
	while (traversal->parent != nullptr)
	{
		traversal = traversal->parent;
		depth++;
	}

	// now we have a depth to check against q
}

template <typename T, typename Node>
Node *ScapegoatTree<T, Node>::remove(Node *node)
{
	Node *removePos = BinaryTree<T, Node>::remove(node);
}