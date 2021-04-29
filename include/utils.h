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
	if (node->left_)
		return node->left_;

	RBNode<T> *curr = node, *parent = curr->parent_;
	while (parent != nullptr && parent->right_ == curr) {
		curr = curr->parent_;
		parent = parent->parent_;
	}
	if (parent == NULL)
		return NULL;

	return parent->right_;
}

#endif
