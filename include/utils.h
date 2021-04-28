// Free, independent utility functions
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "rb_node.h"

template<typename T>
void print_binary_tree(const std::string& prefix, const RBNode<T> *node, bool is_left)
{
	if(node == nullptr)
		return;

	std::cout << prefix;
	std::cout << (is_left ? "├──" : "└──" );

	std::cout << node->value_ << " - " << (node->color_ == 0 ? "black" : "red") << "\n";

	print_binary_tree( prefix + (is_left ? "│   " : "    "), node->left_, true);
	print_binary_tree( prefix + (is_left ? "│   " : "    "), node->right_, false);
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

#endif
