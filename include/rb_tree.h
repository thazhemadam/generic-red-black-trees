#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"
#include "utils.h"
using namespace std;

template <typename T = int, typename Compare = std::less<T>>
class RBTree
{
private:
	RBNode<T> *root_;
	Compare compare;

// rotate functions
	void rotate_left (RBNode<T> *pivot);
	void rotate_right (RBNode<T> *pivot);

// helper functions
	RBNode<T> *copy_tree(RBNode<T> *t);	// helper for copy constructor & assignment operators
	void insert_fixup(RBNode<T> *node);	// helper for insert()

	RBNode<T>* tree_minimum(RBNode<T> *root);
	// helpers for deletion
	void rb_transplant(RBNode<T> * u,RBNode<T> * v);
	void remove_fixup(RBNode<T> *x);

public:
	static RBNode<T> *NIL;
	int tree_size_;

// special functions
	// constructors
	RBTree();				// empty tree
	RBTree(RBNode<T> node);			// tree with a root node
	RBTree(const RBTree<T, Compare> &rhs);	// copy constructor

	// operator function
	template<typename O, typename CO>
	friend std::ostream& operator<<(std::ostream& os, const RBTree<O, CO>& tree);

// Iterator class
	class Iterator;
	Iterator root()
	{
		return Iterator(root_);
	}
	Iterator begin()
	{
		return Iterator(tree_minimum(root_));
	}

// operations on tree
	// insert a node
	Iterator insert(const T& value);
	Iterator insert(RBNode<T> *node);

	// remove a node
	void remove(const T value);
	void remove(RBNode<T> *node);
	void remove(Iterator it);
	void remove(Iterator start, Iterator end);

// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	
// display functions
	void display(std::ostream& os = std::cout) const;
	void print_inorder() const;
	void print_preorder() const;
	void print_postorder() const;


//search functions
	RBNode<T>* search(T value);
	RBNode<T>* search(RBNode<T> *node);
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


// operations on trees
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

		if(compare(node->value_ , temp->value_))
			temp = temp->left_;

		else
			temp = temp->right_;

	}

	node->parent_ = parent;

	if(parent == NIL)
		root_ = node;

	else if(compare(node->value_ , parent->value_))
		parent->left_ = node;

	else
		parent->right_ = node;

	node->left_ = NIL;
	node->right_ = NIL;
	node-> color_ = RED;

	++tree_size_;
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


template<typename T, typename Compare>
std::ostream& operator<<(std::ostream& os, const RBTree<T, Compare>& tree)
{
	tree.display(os);
	return os;
}


template<typename T,typename Compare>
RBNode<T>* RBTree<T,Compare>::search(T value)
{
	RBNode<T>* node = new RBNode<T>(value);
	return search(node);
}

template<typename T,typename Compare>
RBNode<T>* RBTree<T,Compare>::search(RBNode<T> *pivot)
{

	RBNode<T> *temp = root_;

	while(temp != NIL) {
		if(temp->value_ == pivot->value_)
			return temp;

		if(compare(temp->value_, pivot->value_))
			temp=temp->right_;

		else
			temp=temp->left_;
	}

	return nullptr;
}


template<typename T,typename Compare>
void RBTree<T, Compare>::rb_transplant(RBNode<T> *u,RBNode<T> *v)
{
	if(u->parent_ == NIL)
		root_ = v;

	else if(u == u->parent_->left_)
		u->parent_->left_=v;

	else
		u->parent_->right_ = v;

	v->parent_=u->parent_;
}


template<typename T,typename Compare>
void RBTree<T, Compare>::remove(const T value)
{
	RBNode<T>* it = search(value);
	// TODO: RETURN VALUE OF SEARCH TO BE MODIFIED to be an iterator!!!
	if(it == nullptr) {
		cout << "\nNode with value : " << value << "does not exist.";
		return;
	}

	remove(it);
}


template<typename T,typename Compare>
void RBTree<T, Compare>::remove(Iterator it)
{
	remove(&(*it));
}

template<typename T,typename Compare>
void RBTree<T, Compare>::remove(Iterator start, Iterator end)
{
	for(Iterator it = start; it != end; ++it)
		remove(&(*it));
}


template<typename T,typename Compare>
RBNode<T>* RBTree<T, Compare>::tree_minimum(RBNode<T> *root)
{
	RBNode<T> *temp = root;
	while(temp -> left_ != NIL) {
		temp = temp->left_;
	}
	return temp;
} 


template<typename T,typename Compare>
void RBTree<T, Compare>::remove_fixup(RBNode<T> *node)
{
	RBNode<T>* sibling;

	while(node != root_ && node->color_ == BLACK) {

		if(node == node->parent_->left_) {
			sibling = node->parent_->right_;

			if(sibling->color_ == RED) {
				sibling->color_ = BLACK;
				node->parent_->color_ = RED;
				rotate_left(node->parent_);
				sibling = node->parent_->right_;
			}

			if(!sibling->left_ && !sibling->right_) 	// sibling is a NIL node
				break;

			if(sibling->left_->color_ == BLACK && sibling->right_->color_ == BLACK) {
				sibling->color_ = RED;
				node = node->parent_;
			}

			else {
				if(sibling->right_->color_ == BLACK) {
					sibling->left_->color_ = BLACK;
					sibling->color_ = RED;
					rotate_right(sibling);
					sibling = node->parent_->right_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = BLACK;
				sibling->right_->color_ = BLACK;
				rotate_left(node->parent_);
				node = root_;
			}
		}

		else {
			sibling = node->parent_->left_;
			if(sibling->color_ == RED) {
				sibling->color_ = BLACK;
				node->parent_->color_ = RED;
				rotate_right(node->parent_);
				sibling = node->parent_->left_;
			}

			if(!sibling->left_ && !sibling->right_)	// sibling is a NIL node
				break;

			if(sibling->right_->color_ == BLACK && sibling->left_->color_ == BLACK) {
				sibling->color_ = RED;
				node = node->parent_;
			}

			else {
				if(sibling->left_->color_ == BLACK) {
					sibling->right_->color_ = BLACK;
					sibling->color_ = RED;
					rotate_left(sibling);
					sibling = node->parent_->left_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = BLACK;
				sibling->left_->color_ = BLACK;
				rotate_right(node->parent_);
				node = root_;
			}
		}
	}
	node->color_ = BLACK;
}


template<typename T,typename Compare>
void RBTree<T, Compare>::remove(RBNode<T> *node)
{
	RBNode<T> *x;
	RBNode<T> *y = node;
	Color y_original_color = y->color_;
	if(node->left_ == NIL) {
		x = node->right_;
		rb_transplant(node, node->right_);
	}

	else if(node->right_ == NIL) {
		x = node->left_;
		rb_transplant(node, node->left_);
	}

	else {
		y = tree_minimum(node->right_);
		y_original_color = y->color_;
		x = y->right_;

		if(y->parent_ == node)
			x->parent_ == y;

		else {
			rb_transplant(y, y->right_);
			y->right_ = node->right_;
			y->right_->parent_ = y;
		}
		rb_transplant(node, y);
		y->left_ = node->left_;
		y->left_->parent_ = y;
		y->color_ = node->color_;
	}

	if(y_original_color == BLACK)
		remove_fixup(x);
	delete node;
	--tree_size_;
}


template<typename T, typename Compare>
void RBTree<T, Compare>::display(std::ostream& os) const
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
void RBTree<T, Compare>::print_inorder() const
{
	inorder(root_);
}


template<typename T, typename Compare>
void RBTree<T, Compare>::print_preorder() const
{
	preorder(root_);
}


template<typename T, typename Compare>
void RBTree<T, Compare>::print_postorder() const
{
	postorder(root_);
}

#endif