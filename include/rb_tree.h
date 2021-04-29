#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"
#include "utils.h"
using namespace std;

template <typename T>
class RBTree
{

public:
	void rotate_left (RBNode<T> *pivot);	// to be made private
	void rotate_right (RBNode<T> *pivot);   // to be made private
	RBNode<T> *root_;			// to be made private
	static RBNode<T> *NIL;			// to be made private

// special functions
	// constructor
	RBTree();

	// operator function
	template<typename O>
	friend ostream& operator<<(ostream& os, const RBTree<O>& tree);

// Iterator class
	class Iterator;
	Iterator begin();
	Iterator end();

// operations on tree
#ifdef RBT_UNIQUE	//TODO
	pair<Iterator, bool> insert(T& value);
	pair<Iterator, bool> insert(RBNode<T> *node);
#else
	Iterator insert(T& value);
	Iterator insert(RBNode<T> *node);
#endif

	bool delete_node(const T& value);

// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	bool adjust_RBdelete(RBNode<T> *&node);
	int getColor(RBNode<T> *&node);
	void setColor(RBNode<T> *&node, int color);

// display functions
	void print_inorder();
	void print_preorder();
	void print_postorder();
	void tree_insert(RBNode<T> *node);	// to be made private

private:
	int tree_size_;
};

// constructors
template <typename T>
RBNode<T> *RBTree<T>::NIL = nullptr;

// constructors
template<typename T>
RBTree<T>::RBTree()
{
	root_ = nullptr;
	tree_size_ = 0;
}

// operations on trees

//Insertion
template<typename T>
void RBTree<T>::tree_insert(RBNode<T> *node)
{
	RBNode<T> *y = NIL;
	RBNode<T> *x = root_;

	while (x != NIL){
		y = x;

		if(node->value_ < x->value_)
			x = x->left_;
		else
			x = x->right_;
	}
	node->parent_ = y;

	if(y == NIL)
		root_ = node;

	if(node->value_ < y->value_)
		y->left_ = node;
	else
		y-> right_ = node;

}

#ifdef RBT_UNIQUE
template<typename T>
pair<typename RBTree<T>::Iterator, bool> RBTree<T>::insert(T& value)
{
	// Top Down Insertion
	RBNode<T> *curr = root_, *parent = NIL, *new_node;

	// either find the location to insert new node at, or find the value pre-existing in the tree
	while(curr != NIL)  {

		if(curr->value_ = value) {
			// should should <Iterator of pre-existing node with same value, false>
			return pair<Iterator, bool> (Iterator(curr), false);
		}
	}
}

template<typename T>
pair<typename RBTree<T>::Iterator, bool> RBTree<T>::insert(RBTNode<T> *node)


#else


#endif


//rotate functions
template<typename T>
void RBTree<T>::rotate_left(RBNode<T> *pivot)
{
	RBNode<T>* pivot_right = pivot->right_;

	if(pivot_right == NIL)
		return;

	pivot->right_= pivot_right->left_;

	if(pivot_right->left_ != NIL)
		pivot_right->left_->parent_ = pivot;

	pivot_right->parent_ = pivot->parent_;

	if(pivot->parent_ == NIL)
		root_ = pivot_right;

	else if(pivot == pivot->parent_->left_)
		pivot->parent_->left_ = pivot_right;

	else
		pivot->parent_->right_ = pivot_right;

	pivot_right->left_ = pivot;
	pivot->parent_ = pivot_right;
}


template<typename T>
void RBTree<T>::rotate_right(RBNode<T> *pivot)
{
	RBNode<T>* pivot_left = pivot->left_;

	if(pivot_left == NIL)
		return;

	pivot->left_= pivot_left->right_;

	if(pivot_left->right_ != RBTree<T>::NIL)
		pivot_left->right_->parent_ = pivot;

	pivot_left->parent_ = pivot->parent_;

	if(pivot->parent_ == RBTree<T>::NIL)
		root_ = pivot_left;

	else if(pivot == pivot->parent_->right_)
		pivot->parent_->right_ = pivot_left;

	else
		pivot->parent_->left_ = pivot_left;

	pivot_left->right_ = pivot;
	pivot->parent_ = pivot_left;
}


template<typename O>
ostream& operator<<(ostream& os, const RBTree<O>& tree)
{
	os << "_\n";
	print_tree(os, "", tree.root_, false);
	os << "\n";
	return os;
}


/*
// delete the node
template<typename T>
bool RBTree<T>::adjust_RBdelete(RBNode<T> *&node) {
	// nothing to delete
	if (node == nullptr)
		return false;
	
	// removed root_
	if (node == root_) {
		root_ = nullptr;
		return true;
	}
	// CASE 1: if the node is of RED color simply delete it
	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		RBNode<T> *child = node->left != nullptr ? node->left : node->right;
		
		//if node is a left child
		if (node == node->parent->left) {
			// linking the nodes child as the parents child
			node->parent->left = child;
			if (child != nullptr) {
				child->parent = node->parent;
				setColor(child, BLACK);
				delete (node);
			}
		}
		else {
			node->parent->right = child;
			if (child != nullptr){
				child->parent = node->parent;
				setColor(child, BLACK);
				delete (node);
			}
		}
	}
	// if the node is black
	else {
		RBNode<T> *sibling = nullptr;
		RBNode<T> *parent = nullptr;
		RBNode<T> *cur_node = node;
		setColor(cur_node, DOUBLE_BLACK);

		// while the root_ is not double black
		while (cur_node != root_ && getColor(cur_node) == DOUBLE_BLACK) {
			parent = cur_node->parent_;
			// if the node is a left child
			if (cur_node == parent_->left_) {
				sibling = parent->right_;
				// if node's sibling is RED
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotate_left(parent);
				} 

				// if node's sibling is BLACK
				else 
				{   // CASE 3: if DOUBLE BLACK node's sibling's both their children are black
					if (getColor(sibling->left_) == BLACK && getColor(sibling->right_) == BLACK)
					{
						// set sibling to red and parent to BLACK or DOUBLE BLACK depending on its current color
						setColor(sibling, RED);
						if(getColor(parent) == RED)
							setColor(parent, BLACK);
						else {
							setColor(parent, DOUBLE_BLACK);
							// current node is set to a node with DOUBLE BLACK
							cur_node = parent;
						}
					} 
					else {
						// CASE 4 : if DOUBLE BLACK node's sibling's left child is red
						if (getColor(sibling->right_) == BLACK) {
							setColor(sibling->left_, BLACK);
							setColor(sibling, RED);
							rotate_right(sibling);
							sibling = parent->right_;
						}
						// CASE 5 : if DOUBLE BLACK node's sibling's right child is red
						setColor(sibling, parent->color_);
						setColor(parent, BLACK);
						setColor(sibling->right_, BLACK);
						rotate_left(parent);
						break;
					}
				}
			}
			//if the node is a right child : mirror of left operations
			else {
				sibling = parent->left_;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotate_right(parent);
				} 
				else {
				if (getColor(sibling->left_) == BLACK && getColor(sibling->right_) == BLACK) {
					setColor(sibling, RED);
					if (getColor(parent) == RED)
					setColor(parent, BLACK);
					else
					setColor(parent, DOUBLE_BLACK);
					cur_node = parent;
				} 
				else {
					if (getColor(sibling->left_) == BLACK) {
						setColor(sibling->right_, BLACK);
						setColor(sibling, RED);
						rotate_left(sibling);
						sibling = parent->left_;
					}
					setColor(sibling, parent->color_);
					setColor(parent, BLACK);
					setColor(sibling->left_, BLACK);
					rotate_right(parent);
					break;
					}
				}
			}
		}
		// CASE 2: if the root_ is DOUBLE BLACK , then simply set root_ to BLACK 
		if (node == node->parent_->left_)
			node->parent_->left_ = nullptr;
			delete(node);
		else
			node->parent_->right_ = nullptr;
			delete(node);
			setColor(root_, BLACK);
		}
	return true;
}

// finding the node for delete
template<typename T>
RBNode<T>* deleteBST(const RBNode<T> *& root, int val) {
	if (root == nullptr)
		return root;
	
	if (val < root->value_)
		return deleteBST(root->left_, val);
	
	if (val > root->value_)
		return deleteBST(root->right_, val);
	
	if (root->left_ == nullptr || root->right_ == nullptr)
		return root;
	
	// finding the inorder successor 
	RBNode<T> *temp = successor(root);
	// copying the leaf to the root which doen't involve color change
	root->value_ = temp->value_;
	return deleteBST(root->right_, temp->value_);
}

// Interface for delete
template<typename T>	
bool RBTree<T>::delete_node(const T& value) {

	RBNode<T> *node = deleteBST(root_, value);
	return adjust_RBdelete(node);
}
*/

// Free Functions
template<typename T>
RBNode<T> * successor(const RBNode<T> *& pivot)
{
	 RBNode<T> *cur_node = pivot->right_;

	while (cur_node->left_ != nullptr)
		cur_node = cur_node->left_;

	return cur_node;
}

template<typename T>
RBNode<T> * predecessor(const RBNode<T> *& pivot)
{
	 RBNode<T> *cur_node = pivot->left_;

	while (cur_node->right_ != nullptr)
		cur_node = cur_node->right_;

	return cur_node;
}

//Utitlity Functions
template<typename T>
int RBTree<T>::getColor(RBNode<T> *&node) {
	if (node == nullptr)
		return BLACK;

	return node->color_;
}

template<typename T>
void RBTree<T>::setColor(RBNode<T> *&node, int color) {
	if (node == nullptr)
		return;

	node->color_ = color;
}

template<typename T>
void RBTree<T>::print_inorder()
{
	inorder(root_);
}

template<typename T>
void RBTree<T>::print_preorder()
{
	preorder(root_);
}

template<typename T>
void RBTree<T>::print_postorder()
{
	postorder(root_);
}

#endif
