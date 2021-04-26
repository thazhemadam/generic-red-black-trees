#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"

using namespace std;

template <typename T>
class RBTree
{
	private:
		int tree_size_;
		RBNode<T> *root_;
		static RBNode<T> *NIL;

		void rotate_left (RBNode<T> *pivot);
		void rotate_right (RBNode<T> *pivot);

	public:
		// special functions
		// constructor
		RBTree();

		class Iterator;
		Iterator begin();
		Iterator end();

		// operations on tree
		pair<Iterator, bool> insert_node(const T& value);

		// utility functions
		inline bool is_empty() const { return tree_size_ == 0; }

		// display functions
		void inorder(RBNode<T> *root);
		void preorder(RBNode<T> *root);
		void postorder(RBNode<T> *root);

};

template <typename T>
RBNode<T> *RBTree<T>::NIL = nullptr;

// constructors
template<typename T>
RBTree<T>::RBTree()
{
	if(NIL == nullptr) {
		NIL = new RBNode<T>(0, NULL, NULL, NULL, BLACK);
	}
	root_ = NIL;
	tree_size_ = 0;
}

// operations on trees
template<typename T>
pair<typename RBTree<T>::Iterator, bool> RBTree<T>::insert_node(const T& value)
{
	// Top Down Insertion
	RBNode<T> *curr = root_, *parent = NIL, *new_node;

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

//rotate functions
template<typename T>
void RBTree<T>::rotate_left(RBNode<T> *pivot)
{
    RBNode<T>* pivot_right = pivot->right_;
    pivot->right_=pivot_right->left_;
    if(pivot_right!=nullptr)
        pivot->right_->parent_=pivot;
        pivot_right->parent_=pivot->parent_;
    if(pivot->parent_==nullptr)
    {
        root=pivot_right;
    }
    else if( pivot== pivot->parent_->left_)
    {
        pivot->parent->left_=pivot_right;
    }
    else
    {
        pivot->parent_->right_=pivot_right;
    }
    pivot_right->left_=pivot;
    pivot->parent_=pivot_right;
}
template<typename T>
void RBTree<T>::rotate_right(RBNode<T> *pivot)
{
    RBNode<T>* pivot_left = pivot->left_;
    pivot->left=pivot_left->right_;
    if(pivot_left!=nullptr)
        pivot->left_->parent_=pivot;
        pivot_left->parent_=pivot->parent_;
    if(pivot->parent_==nullptr)
    {
        root=pivot_left;
    }
    else if( pivot== pivot->parent_->right_)
    {
        pivot->parent->right_=pivot_left;
    }
    else
    {
        pivot->parent_->left_=pivot_left;
    }
    pivot_left->right_=pivot;
    pivot->parent_=pivot_left;
}
// display functions
template<typename T>
void RBTree<T>::inorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	inorder(root->left_);
	cout << root->value_ << "\t";
	inorder(root->right_);

}

template<typename T>
void RBTree<T>::preorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	cout << root->value_ << "\t";
	preorder(root->left_);
	preorder(root->right_);

}

template<typename T>
void RBTree<T>::postorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	postorder(root->left_);
	postorder(root->right_);
	cout << root->value_ << "\t";

}

#endif
