#ifndef NODE_H_
#define NODE_H_

template <typename T>
struct Node
{
	T data;
	Node *left;
	Node *right;
	Node *parent;

	Node(Node *_parent, T _data); // constructor
};

#endif // NODE_H_
