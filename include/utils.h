// Free, independent utility functions
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <queue>
#include "rb_node.h"

template<typename T>
void print_tree(std::ostream& os, const std::string& prefix, const RBNode<T> *node, bool is_left)
{
	if(node -> left_ == nullptr && node->right_ == nullptr)
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
RBNode<T>* levelorder_predecessor(RBNode<T> *root, RBNode<T> *node)
{
    if(root == nullptr)
        return nullptr;

    if(root == node)
    {
        return nullptr;
    }
    std::queue<RBNode<T>*> q;
    q.push(root);
    RBNode<T>* prev= nullptr;
    while(!q.empty()) {
        RBNode<T> *temp = q.front();
        q.pop();
        if(temp==node){
            break;
        }
        else
        {
            prev=temp;
        }
        if(temp -> left_ != nullptr)
            q.push(temp->left_);

        if(temp -> right_ != nullptr)
            q.push(temp->right_);
    }
    return prev;
}
template<typename T>
RBNode<T>* levelorder_successor(RBNode<T> *root, RBNode<T> *node)
{
	if(root == nullptr)
		return nullptr;

	if(root == node) {
		if(root->left_ != nullptr)
			return root->left_;
		else if(root->right_ != nullptr)
			return root->left_;
		else
			return nullptr;
	}
	std::queue<RBNode<T>*> q;
	q.push(root);
	while(!q.empty()) {
		RBNode<T> *temp = q.front();
		q.pop();

		if(temp -> left_ != nullptr)
			q.push(temp->left_);

		if(temp -> right_ != nullptr)
			q.push(temp->right_);
		if(temp == node)
			break;
	}
	return q.front();
}

template<typename T>
RBNode<T>* preorder_predecessor(RBNode<T> *root_,const RBNode<T> *node)
{
    RBNode<T>* parent = node->parent_;
    if (node == root_)
            return nullptr;
        if (parent->left_ == NULL || parent->left_ == node)
        {
            return parent;
        }
    
        RBNode<T>* current = parent->left_;
        while (current->right_ != NULL)
        {
            current = current->right_;
        }
      
        return current;
}

template<typename T>
RBNode<T>* preorder_successor(const RBNode<T> *node)
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

	// leaf node. has an ancestor/is a node which is a left child + has a sibling.
	while(parent != nullptr) {
		if(parent->left_ == node && parent->right_!=nullptr)
			return parent->right_;
		node = parent;
		parent = node->parent_;
	}

	// undefined case.
	return nullptr;
}

template<typename T>
RBNode<T>* postorder_predecessor( RBNode<T>* root, RBNode<T> *node)
{
   // RBNode<T>* parent = node->parent_;
    RBNode<T>* temp = node->right_;
    RBNode<T> *current = node;
    RBNode<T> *parent = node->parent_;
    if (temp!=nullptr)
            return temp;
     
        // If right child does not exist, then
        // travel up (using parent pointers)
        // until we reach a node which is right
        // child of its parent
        while (parent != NULL && parent->left_ == current) {
            current = current->parent_;
            parent = parent->parent_;
        }
     
        // If we reached root, then the given
        // node has no postorder predecessor
        if (parent == NULL)
            return NULL;
     
        return parent->left_;
}

template<typename T>
RBNode<T> *postorder_successor(const RBNode<T> * node)
{
	if(node == nullptr)
		return nullptr;

	if(node -> parent_ == nullptr)	// node is root. undefined case.
		return nullptr;

	RBNode<T> *parent = node->parent_;

	// is the right child, or is a left child with no siblings
	if(node == parent->right_ || parent->right_ == nullptr)
		return parent;

	// is the left child, with a right sibling
	RBNode<T> *temp = parent->right_;
	// until it is the next a leaf node. left-most leafnodes are given priority.
	while(temp->left_ != nullptr || temp->right_ != nullptr) {
		if(temp->left_ != nullptr){
			temp = temp->left_;
			continue;
		}

		else if(temp->right_ != nullptr){
			temp = temp->right_;
			continue;
		}
		
	}

	return temp;
}


template<typename T>
RBNode<T> * inorder_succ(const RBNode<T> * pivot)
{
	 RBNode<T> *cur_node = pivot->right_;

	while (cur_node->left_ != nullptr)
		cur_node = cur_node->left_;

	return cur_node;
}

template<typename T>
RBNode<T> * inorder_pred(const RBNode<T> *& pivot)
{
	 RBNode<T> *cur_node = pivot->left_;

	while (cur_node->right_ != nullptr)
		cur_node = cur_node->right_;

	return cur_node;
}
#endif
