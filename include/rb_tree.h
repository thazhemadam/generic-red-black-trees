#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"
#include "utils.h"
using namespace std;

template <typename T = int, typename Compare = std::less<T>>
class RBTree
{

public:
	RBNode<T> *root_;			// to be made private
	static RBNode<T> *NIL;			// to be made private?

// special functions
	// constructor
	RBTree();	// empty tree
	RBTree(RBNode<T> node);	// tree with a root node
	RBTree(const RBTree<T, Compare> &rhs);

	// operator function
	template<typename O, typename CO>
	friend ostream& operator<<(ostream& os, const RBTree<O, CO>& tree);

// Iterator class
	class Iterator;
	Iterator begin()
	{
		return Iterator(root_);
	}
	Iterator end()
	{
		return NIL;
	}

// operations on tree
#ifdef RBT_UNIQUE	//TODO
	pair<Iterator, bool> insert(const T& value);
	pair<Iterator, bool> insert(const RBNode<T> *node);
#else
	Iterator insert(const T& value);
	Iterator insert(RBNode<T> *node);
#endif

	bool delete_node(const T& value);

// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	bool adjust_RBdelete(RBNode<T> *&node);
	Color getColor(RBNode<T> *&node);
	void setColor(RBNode<T> *&node, Color color);

// display functions
	void display(ostream& os = std::cout) const;
	void print_inorder();
	void print_preorder();
	void print_postorder();

private:
	int tree_size_;
	Compare compare;
	void rotate_left (RBNode<T> *pivot);
	void rotate_right (RBNode<T> *pivot);
	RBNode<T> *copy_tree(RBNode<T> *t);
	void insert_fixup(RBNode<T> *node);


};

// constructors
template <typename T, typename Compare>
RBNode<T> *RBTree<T, Compare>::NIL = new RBNode<T>();


// constructors
template<typename T, typename Compare>
RBTree<T, Compare>::RBTree()
{
	root_ = NIL;
	tree_size_ = 0;
}


template<typename T, typename Compare>
RBTree<T, Compare>::RBTree(RBNode<T> node)
: root_(new RBNode<T>(node)), tree_size_(1)
{
	root_->color_ = BLACK;
}


// copy ctor
template<typename T, typename Compare>
RBTree<T, Compare>::RBTree(const RBTree<T, Compare> &rhs)
: tree_size_(rhs.tree_size_)
{
	if(rhs.root_ == NIL) {
		root_ = NIL;
		return;
	}

	root_ = copy_tree(rhs.root_);
}


template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::copy_tree(RBNode<T> *root)
{
	RBNode<T> *new_left, *new_right, *new_node;
	if(root == NIL)
		return NIL;

	new_left = copy_tree(root->left_);
	new_right = copy_tree(root->right_);

	new_node = new RBNode<int>(*root);
	new_node -> left_ = new_left;
	new_node-> right_ = new_right;

	if(new_left != nullptr)
		new_left -> parent_ = new_node;


	if(new_right != nullptr)
		new_right -> parent_ = new_node;

	return new_node;
}


// operations on trees
#ifdef RBT_UNIQUE
template<typename T, typename Compare>
pair<typename RBTree<T, Compare>::Iterator, bool> RBTree<T, Compare>::insert(T& value)
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

template<typename T, typename Compare>
pair<typename RBTree<T, Compare>::Iterator, bool> RBTree<T, Compare>::insert(RBTNode<T> *node)


#else
template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::insert(const T& value)
{
	RBNode<T> *node = new RBNode<T>(value);
	RBTree<T, Compare>::Iterator it = insert(node);
	return it;
}


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::insert(RBNode<T> *node)
{
	RBTree<T, Compare>::Iterator it = Iterator(node);
	RBNode<T> *parent = NIL;
	RBNode<T> *temp = root_;

	while(temp != NIL) {
		parent = temp;

		// if(RBNode<T>::compare(node->value_, temp->value_))
		if(compare(node->value_ , temp->value_))
			temp = temp->left_;

		else
			temp = temp->right_;

	}

	node->parent_ = parent;

	if(parent == NIL)
		root_ = node;

	// if(RBNode<T>::compare(node->value_, temp->value_))
	else if(compare(node->value_ , parent->value_))
		parent->left_ = node;

	else
		parent->right_ = node;

	node->left_ = NIL;
	node->right_ = NIL;
	node-> color_ = RED;
	++tree_size_;
	// display();
	insert_fixup(node);
	return it;
}


template<typename T, typename Compare>
void RBTree<T, Compare>::insert_fixup(RBNode<T> *node)
{
	while(node->parent_->color_ == RED) {
		if(node->parent_ == node->parent_->parent_->left_) {
			RBNode<T> *y = node->parent_->parent_->right_;
			if(y->color_ == RED) {
				node->parent_->color_ = BLACK;
				y->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if(node == node->parent_->right_) {
					node = node->parent_;
					rotate_left(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rotate_right(node->parent_->parent_);
			}
		}
		else {
			RBNode<T> *y = node->parent_->parent_->left_;
			if(y->color_ == RED) {
				node->parent_->color_ = BLACK;
				y->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if(node == node->parent_->left_) {
					node = node->parent_;
					rotate_right(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rotate_left(node->parent_->parent_);
			}

		}
	}
	root_->color_ = BLACK;
}


#endif


//rotate functions
template<typename T, typename Compare>
void RBTree<T, Compare>::rotate_left(RBNode<T> *pivot)
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


template<typename T, typename Compare>
void RBTree<T, Compare>::rotate_right(RBNode<T> *pivot)
{
	RBNode<T>* pivot_left = pivot->left_;

	if(pivot_left == NIL)
		return;

	pivot->left_= pivot_left->right_;

	if(pivot_left->right_ != RBTree<T, Compare>::NIL)
		pivot_left->right_->parent_ = pivot;

	pivot_left->parent_ = pivot->parent_;

	if(pivot->parent_ == RBTree<T, Compare>::NIL)
		root_ = pivot_left;

	else if(pivot == pivot->parent_->right_)
		pivot->parent_->right_ = pivot_left;

	else
		pivot->parent_->left_ = pivot_left;

	pivot_left->right_ = pivot;
	pivot->parent_ = pivot_left;
}


template<typename T, typename Compare>
ostream& operator<<(ostream& os, const RBTree<T, Compare>& tree)
{
	tree.display(os);
	return os;
}



#if 0
// delete the node
template<typename T, typename Compare>
bool RBTree<T, Compare>::adjust_RBdelete(RBNode<T> *&node) {
	// nothing to delete
	if (node == nullptr)
		// return false;
	
	// removed root_
	if (node == root_) {
		root_ = nullptr;
		return true;
	}
	// CASE 1: if the node is of RED color simply delete it
	if (getColor(node) == RED || getColor(node->left_) == RED || getColor(node->right_) == RED) {
		RBNode<T> *child = node->left_ != nullptr ? node->left_ : node->right_;
		
		//if node is a left child
		if (node == node->parent_->left_) {
			// linking the nodes child as the parents child
			node->parent->left_ = child;
			if (child != nullptr) {
				child->parent_ = node->parent;
				setColor(child, BLACK);
				delete (node);
			}
		}
		else {
			node->parent->right_ = child;
			if (child != nullptr){
				child->parent_ = node->parent;
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
		setColor(cur_node, BLACK);

		// while the root_ is not double black
		while (cur_node != root_ && getColor(cur_node) == BLACK) {
			parent = cur_node->parent_;
			// if the node is a left child
			if (cur_node == parent->left_) {
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
							setColor(parent, BLACK);
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
		if (node == node->parent_->left_){
			node->parent_->left_ = nullptr;
			delete(node);
			setColor(root_, BLACK);}
		else {
			node->parent_->right_ = nullptr;
			delete(node);
			setColor(root_, BLACK);}
		}
	return true;
}

// finding the node for delete
template<typename T, typename Compare>
RBNode<T>* deleteBST(RBNode<T> * root, int val) {
	if (root == nullptr)
		return root;
	
	if (val < root->value_)
		return deleteBST(root->left_, val);
	
	if (val > root->value_)
		return deleteBST(root->right_, val);
	
	// if (root->left_ == nullptr || root->right_ == nullptr)
	if (root->value_==val)// == nullptr || root->right_ == nullptr)
		return root;
	
	// finding the inorder successor 
	RBNode<T> *temp = successor(root);
	// copying the leaf to the root which doen't involve color change
	root->value_ = temp->value_;
	return deleteBST(root->right_, temp->value_);
}

// Interface for delete
template<typename T, typename Compare>	
bool RBTree<T, Compare>::delete_node(const T& value) {

	RBNode<T> *node = deleteBST(root_, value);
	return adjust_RBdelete(node);
}
#endif


//Utitlity Functions
template<typename T, typename Compare>
Color RBTree<T, Compare>::getColor(RBNode<T> *&node) {
	if (node == nullptr)
		return BLACK;

	return node->color_;
}

template<typename T, typename Compare>
void RBTree<T, Compare>::setColor(RBNode<T> *&node, Color color) {
	if (node == nullptr)
		return;

	node->color_ = color;
}

template<typename T, typename Compare>
void RBTree<T, Compare>::display(ostream& os) const
{
	if(root_ == nullptr) {
		os << "\nTree does not exist.\n";
		return;
	}

	os << "_\n";
	print_tree(os, "", root_, false);
	os << "\n";

}

template<typename T, typename Compare>
void RBTree<T, Compare>::print_inorder()
{
	inorder(root_);
}

template<typename T, typename Compare>
void RBTree<T, Compare>::print_preorder()
{
	preorder(root_);
}

template<typename T, typename Compare>
void RBTree<T, Compare>::print_postorder()
{
	postorder(root_);
}

#endif
