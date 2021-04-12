#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"

using namespace std;

template <typename T>
class RBTree
{
	private:
		int tree_size;
		RBNode<T> *root;
		static RBNode<T> *NIL;

	public:
		// special functions
		// constructor
		RBTree();

		class Iterator;
		Iterator begin();
		Iterator end();

		// operations on tree

		// if value is not present in the tree, insert it and return a pair - with the iterator pointing to the node where the value was inserted, and the bool value = true.
		// if value is already present in the tree, return a pair - with the iterator pointing to the existing item, and the bool value = false.

		pair<Iterator, bool> insert_node(const T& value);

		// display functions
		void inorder(RBNode<T> *root);
		void preorder(RBNode<T> *root);
		void postorder(RBNode<T> *root);

};

template <typename T>
RBNode<T> *RBTree<T>::NIL = nullptr;

template<typename T>
RBTree<T>::RBTree()
{
	if(NIL == nullptr) {
		NIL = new RBNode<T>(0, NULL, NULL, NULL, BLACK);
	}
	root = NIL;
	tree_size = 0;
}

template<typename T>
pair<typename RBTree<T>::Iterator, bool> RBTree<T>::insert_node(const T& value)
{
	// Top Down Insertion
	RBNode<T> *curr = root, *parent = NIL, *new_node;

	// either find the location to insert new node at, or find the value pre-existing in the tree
	while(curr != NIL)  {
		#ifdef RBT_UNIQUE
		if(curr->value_ = value) {
			// should should <Iterator of pre-existing node with same value, false>
			return pair<Iterator, bool> (Iterator(curr), false);
		}
		#endif
	}
}

template<typename T>
void RBTree<T>::inorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	inorder(root->get_left());
	cout << root->get_value() << "\t";
	inorder(root->get_right());

}

template<typename T>
void RBTree<T>::preorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	cout << root->get_value() << "\t";
	preorder(root->get_left());
	preorder(root->get_right());

}

template<typename T>
void RBTree<T>::postorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	postorder(root->get_left());
	postorder(root->get_right());
	cout << root->get_value() << "\t";

}

#endif
