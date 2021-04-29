// Free, independent utility functions
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "rb_node.h"

template<typename T>
void print_tree(std::ostream& os, const std::string& prefix, const RBNode<T> *node, bool is_left)
{
	if(node == nullptr)
		return;

	os << prefix;
	os << (is_left ? "├──" : "└──" );

	os << node->value_ << " - " << (node->color_ == 0 ? "black" : "red") << "\n";

	print_tree(os, prefix + (is_left ? "│   " : "    "), node->left_, true);
	print_tree(os, prefix + (is_left ? "│   " : "    "), node->right_, false);
}

template<typename T>
void inorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	inorder(root->left_);
	std::cout << root->value_ << "\t";
	inorder(root->right_);

}

template<typename T>
void preorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	std::cout << root->value_ << "\t";
	preorder(root->left_);
	preorder(root->right_);

}


template<typename T>
void postorder(RBNode<T> *root)
{
	if (root == nullptr)
		return;

	postorder(root->left_);
	postorder(root->right_);
	std::cout << root->value_ << "\t";

}


template<typename T>
RBNode<T>* preorder_successor(RBNode<T> *node)
{
	if(node == nullptr)
		return nullptr;

	if (node->left_)		// has left child.
		return node->left_;

	else if (node->right_)		// has right child.
		return node->right_;

	if(node->parent_ == nullptr)	// has no children, and is root.
		return nullptr;

	RBNode<T> *parent = node->parent_;

	if(node == parent->left_ && parent->right_ != nullptr)	// leaf node, which has a right sibling.
		return parent->right_;

	// leaf node. has an ancestor, which is a left child, with a right sibling
	RBNode<T> *ancestor = node->parent_;
	parent = ancestor->parent_;		// parent is the parent of the ancestor
	while ((parent != nullptr) && (parent->left_ != ancestor) && (parent->right_ == nullptr)) {
		ancestor = parent;
		parent = ancestor->parent_;
	}

	if(ancestor == parent->left_)
		return parent -> right_;

	// undefined case.
	return nullptr;
}

#endif
