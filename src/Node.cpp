#include "../include/Node.h"

template <typename T>
Node<T>::Node(Node *_parent, const T _data)
{
	left = nullptr;
	right = nullptr;

	parent = _parent;

	data = _data;
}
