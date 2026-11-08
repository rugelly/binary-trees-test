#ifndef NODESCAPEGOAT_H_
#define NODESCAPEGOAT_H_

#include "../include/Node.h"

template <typename T>
struct NodeScapegoat : Node<T>
{
	int size; // size of subtree this node is parent of (includes this node)
};

#endif // NODESCAPEGOAT_H_
