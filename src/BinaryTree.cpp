#include "../include/BinaryTree.h"

// #region Constructors
template <typename T, typename Node>
BinaryTree<T, Node>::BinaryTree()
{
	root = nullptr;
}

template <typename T, typename Node>
BinaryTree<T, Node>::BinaryTree(const BinaryTree<T, Node> &copy)
{
	root = copyHelper(copy.root, nullptr); // root has no parent
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::copyHelper(Node *srcNode, Node *newParent)
{
	// need a guard clause if we havent given it a node to work with
	if (srcNode == nullptr)
		return nullptr;

	// allocate new node
	Node *newNode = new Node(newParent, srcNode->data);

	// recursively create new nodes down the left and right sides of tree
	newNode->left = copyHelper(srcNode->left, newNode);
	newNode->right = copyHelper(srcNode->right, newNode);

	return newNode;
}
// #endregion

// #region Member Functions
template <typename T, typename Node>
int BinaryTree<T, Node>::depth(Node *node)
{
	int depth = 0;
	while (node != root)
	{
		node = node->parent;
		depth++;
	}
	return depth;
}

template <typename T, typename Node>
int BinaryTree<T, Node>::size(Node *node)
{
	if (node == nullptr)
		return 0;

	return 1 + size(node->left) + size(node->right);
}

template <typename T, typename Node>
int BinaryTree<T, Node>::height(Node *node)
{
	if (node == nullptr)
		return -1;

	return 1 + std::max(height(node->left), height(node->right));
}
// #endregion

// #region Traversal
template <typename T, typename Node>
void BinaryTree<T, Node>::preorder(Node *node)
{
	if (node == nullptr)
		return;

	std::cout << node->data << ", ";
	preorder(node->left);
	preorder(node->right);
}

template <typename T, typename Node>
void BinaryTree<T, Node>::inorder(Node *node)
{
	if (node == nullptr)
		return;

	inorder(node->left);
	std::cout << node->data << ", ";
	inorder(node->right);
}

template <typename T, typename Node>
void BinaryTree<T, Node>::postorder(Node *node)
{
	if (node == nullptr)
		return;

	postorder(node->left);
	postorder(node->right);
	std::cout << node->data << ", ";
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::preorderNext(Node *node, T targetValue)
{
	if (node == nullptr)
		return nullptr;

	// found the node we want
	if (node->data == targetValue)
	{
		if (node->left != nullptr)
			return node->left;

		if (node->right != nullptr)
			return node->right;

		// recursively go backwards up the tree
		return preorderRecurseBack(node);
	}

	// regular preorder traversal to find the matching node value
	Node *left = preorderNext(node->left, targetValue);
	Node *right = preorderNext(node->right, targetValue);

	if (left != nullptr)
		return left;
	if (right != nullptr)
		return right;

	return nullptr;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::preorderRecurseBack(Node *node)
{
	// some guard clauses to check if we end up at the tree root
	if (node->parent == nullptr)
		return nullptr;

	// just in case
	if (node == nullptr)
		return nullptr;

	// are we the left node under our parent?
	if (node->parent->left == node)
	{
		// if there is a right under our parent, its the next node
		if (node->parent->right != nullptr)
			return node->parent->right;
	}

	// otherwise, go up a level and try again
	return preorderRecurseBack(node->parent);
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::inorderNext(Node *node, T targetValue)
{
	if (node == nullptr)
		return nullptr;

	// inorder is left, node, right
	Node *left = inorderNext(node->left, targetValue);
	if (left != nullptr)
		return left;

	// if our target has a right child
	if (node->data == targetValue)
	{
		if (node->right != nullptr)
			// keep traversing left children from there until leaf found
			return inorderRecurseDown(node->right);

		// no right child, so we need to step back up the tree to find:
		// a node that the target is connected to via a left child
		return inorderRecurseBack(node);
	}

	Node *right = inorderNext(node->right, targetValue);
	if (right != nullptr)
		return right;

	return nullptr;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::inorderRecurseDown(Node *node)
{
	// we stop when we hit a leaf
	if (node == nullptr)
		return nullptr;

	// hit the end of left nodes, target found
	if (node->left == nullptr)
		return node;

	// otherwise keep going down to the left
	return inorderRecurseDown(node->left);
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::inorderRecurseBack(Node *node)
{
	// some guard clauses to check if we end up at the tree root
	if (node->parent == nullptr)
		return nullptr;

	// just in case
	if (node == nullptr)
		return nullptr;

	// we need to find a parent that we are a left child of
	if (node->parent->left == node)
		return node->parent;

	// otherwise keep going up
	return inorderRecurseBack(node->parent);
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::postorderNext(Node *node, T targetValue)
{
	if (node == nullptr)
		return nullptr;

	// postorder is left, right, node
	Node *left = postorderNext(node->left, targetValue);
	if (left != nullptr)
		return left;
	Node *right = postorderNext(node->right, targetValue);
	if (right != nullptr)
		return right;

	if (node->data == targetValue)
	{
		// if we are a right node, our parent is next
		if (node->parent->right == node)
			return node->parent;

		// we are left node, and we dont have a right pair, parent is next again
		if (node->parent->right == nullptr)
			return node->parent;

		// have a paired right, find the leftmost leaf under it
		return postorderRecurseDown(node->parent->right);
	}

	return nullptr;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::postorderRecurseDown(Node *node)
{
	// guard
	if (node == nullptr)
		return nullptr;

	// found our target
	if (node->left == nullptr)
		return node;

	// continue down the left branches
	return postorderRecurseDown(node->left);
}
// #endregion

// #region BST Verification
template <typename T, typename Node>
bool BinaryTree<T, Node>::verifyHelper(Node *node, T min, T max)
{
	if (node == nullptr)
		return true;

	if (node->data > min && node->data < max)
	{
		if (!verifyHelper(node->left, min, node->data))
			return false;
		return verifyHelper(node->right, node->data, max);
	}
	else
	{
		return false;
	}
}

template <typename T, typename Node>
bool BinaryTree<T, Node>::verifyOrderProperty(Node *node)
{
	return verifyHelper(node, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

// #endregion

// #region Tree Functions
template <typename T, typename Node>
Node *BinaryTree<T, Node>::insertHelper(Node *prev, Node *_root, T data)
{
	// whenever there is no node, that is where we make it and return the ptr
	if (_root == nullptr)
	{
		Node *newNode = new Node(prev, data);

		// special case if this is the very first node inserted into the tree
		if (!root)
			root = newNode;

		if (prev != nullptr)
		{
			if (newNode->data < prev->data)
			{
				std::cout << "[" << newNode->data << ']' << "<-" << prev->data;
			}

			else
			{
				std::cout << ' ' << prev->data << "->" << "[" << newNode->data << ']';
			}
		}
		else
		{
			std::cout << "ROOT=[" << newNode->data << ']';
		}

		std::cout << '\n';

		return newNode;
	}

	// smaller goes left, bigger goes right. prev node trails behind (to be assigned as parent)
	if (data < _root->data)
		_root->left = insertHelper(_root, _root->left, data);
	else if (data > _root->data)
		_root->right = insertHelper(_root, _root->right, data);

	// otherwise send back the root
	return _root;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::insert(T data)
{
	return insertHelper(nullptr, root, data);
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::findHelper(Node *node, T key)
{
	// no root so just return the nullptr
	if (node == nullptr)
		return node;

	// special case if we are looking for the root stop now
	if (node->data == key)
		return node;

	// greater? search the right
	if (node->data < key)
		return findHelper(node->right, key);

	// smaller goes left
	return findHelper(node->left, key);
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::find(T key)
{
	Node *node = findHelper(root, key);
	if (node == nullptr)
	{
		std::cout << "Node value \"" << key << "\" was not found in the tree.\n";
		return nullptr;
	}
	else
	{
		std::cout << "found node \"" << node->data << "\"\n";
		return node;
	}
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::remove(Node *node)
{
	// to remove a node follow the rules that Pat Morin lays out:
	// - a leaf can just be snipped off
	// - a node with only one child can be deleted and have that child take its spot
	// - with 2 children: traverse the right side under the node and find the leftmost leaf
	//		delete the node and move that leaf into its spot

	if (!node)
		return nullptr;

	// no kids? delete and return null
	if (node->left == nullptr && node->right == nullptr)
	{
		// clean up parent link to this node
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else if (node == node->parent->right)
			node->parent->right = nullptr;

		std::cout << "deleted \"" << node->data << "\"\n";
		delete node;
		return nullptr;
	}

	// only left kid? or only right kid?
	if (node->left != nullptr && node->right == nullptr)
	{
		return removeSingleChildHelper(node, node->left);
	}
	else if (node->left == nullptr && node->right != nullptr)
	{
		return removeSingleChildHelper(node, node->right);
	}

	// node has both kids
	if (node->left != nullptr && node->right != nullptr)
	{
		// find leftmost kid under right side
		Node *leftmost = findLeftmost(node->right);
		std::cout << "overwrite \"" << node->data << "\" with \"" << leftmost->data << "\" - the old \"" << leftmost->data << "\" will be deleted. ";
		// overwrite our 'deleted' node with the found nodes data
		node->data = leftmost->data;
		// perform a regular removal on the now 'obsolete' node
		// (which shold be one of the above only left? only right? removes)
		remove(leftmost);
	}

	return node;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::removeSingleChildHelper(Node *node, Node *subtree)
{
	Node *oldNode = node;
	Node *parent = node->parent;

	// parent needs to link to subtree correctly
	if (oldNode == parent->left)
		parent->left = subtree;
	else if (oldNode == parent->right)
		parent->right = subtree;

	// subtree also needs to link to the parent, cutting oldNode out of the tree
	subtree->parent = oldNode->parent;

	std::cout << "deleting \"" << oldNode->data << "\". Replaced with: " << subtree->data << '\n';

	// now we can remove the target
	delete oldNode;

	// and return what is now in its place
	return subtree;
}

template <typename T, typename Node>
Node *BinaryTree<T, Node>::findLeftmost(Node *node)
{
	if (node == nullptr)
		return nullptr;

	if (node->left != nullptr)
		return findLeftmost(node->left);

	return node;
}
// #endregion

// #region Printing
template <typename T, typename Node>
void BinaryTree<T, Node>::print()
{
	int i = 0;
	while (i <= height(root))
	{
		printlv(i);
		i++;
		std::cout << std::endl;
	}
	std::cout << '\n';
}

template <typename T, typename Node>
void BinaryTree<T, Node>::printlv(int n)
{
	Node *temp = root;
	int val = std::pow(2, height(root) - n + 2);
	std::cout << std::setw(val) << "";
	dispLV(temp, n, val);
}

template <typename T, typename Node>
void BinaryTree<T, Node>::dispLV(Node *p, int lv, int d)
{
	int disp = 2 * d;
	if (lv == 0)
	{
		if (p == nullptr)
		{

			std::cout << " . ";
			std::cout << std::setw(disp - 3) << "";
			return;
		}
		else
		{
			int result = ((p->data <= 1) ? 1 : log10(p->data) + 1);
			std::cout << " " << p->data << " ";
			std::cout << std::setw(disp - result - 2) << "";
		}
	}
	else
	{
		if (p == nullptr && lv >= 1)
		{
			dispLV(nullptr, lv - 1, d);
			dispLV(nullptr, lv - 1, d);
		}
		else
		{
			dispLV(p->left, lv - 1, d);
			dispLV(p->right, lv - 1, d);
		}
	}
}
// #endregion
