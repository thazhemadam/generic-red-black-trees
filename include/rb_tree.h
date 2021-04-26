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
		bool delete_node(const T& value);

	// utility functions
		inline bool is_empty() const { return tree_size_ == 0; }
		bool adjust_RBdelete(RBNode<T> *&node);
		int getColor(RBNode<T> *&node);
		void setColor(RBNode<T> *&node, int color);

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
	if(NIL == nullptr)
		NIL = new RBNode<T>(0, NULL, NULL, NULL, BLACK);

	root_ = NIL;
	tree_size_ = 0;
}

// operations on trees

//Insertion
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
		root=pivot_right;

	else if( pivot== pivot->parent_->left_)
		pivot->parent->left_=pivot_right;

	else
		pivot->parent_->right_=pivot_right;

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
		root=pivot_left;
	else if( pivot== pivot->parent_->right_)
		pivot->parent->right_=pivot_left;
	else
		pivot->parent_->left_=pivot_left;

	pivot_left->right_=pivot;
	pivot->parent_=pivot_left;
}

// delete the node
template<typename T>
bool RBTree<T>::adjust_RBdelete(RBNode<T> *&node) {
	// nothing to delete
	if (node == nullptr)
		return false;
	
	// removed root
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

		// while the root is not double black
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
		// CASE 2: if the root is DOUBLE BLACK , then simply set root to BLACK 
		if (node == node->parent_->left_)
			node->parent_->left_ = nullptr;
			delete(node);
		else
			node->parent_->right_ = nullptr;
			delete(node);
			setColor(root, BLACK);
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
