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
	friend std::ostream& operator<<(std::ostream& os, const RBTree<O, CO>& tree);

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

// delete functions
	void delete_node(RBNode<T>* node);
	void deleteVal(int value_);


// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	
// display functions
	void display(std::ostream& os = std::cout) const;
	void print_inorder();
	void print_preorder();
	void print_postorder();


//search functions
	RBNode<T>* search(T value);
	RBNode<T>* search(RBNode<T> *node);
private:
	int tree_size_;
	Compare compare;
	void rotate_left (RBNode<T> *pivot);
	void rotate_right (RBNode<T> *pivot);

	RBNode<T> *copy_tree(RBNode<T> *t);
	void insert_fixup(RBNode<T> *node);

	RBNode<T>* find_node(int val);

	void rb_transplant(RBNode<T> * u,RBNode<T> * v);
	RBNode<T>* tree_minimum(RBNode<T> *root);
	void delete_fixup(RBNode<T> *x);
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
std::ostream& operator<<(std::ostream& os, const RBTree<T, Compare>& tree)
{
	tree.display(os);
	return os;
}


template<typename T,typename Compare>
RBNode<T>* RBTree<T,Compare>::search(T value)
{
	RBNode<T>* node = new RBNode<T>(value);
	cout << node->value_ << endl;
	return search(node);
}

template<typename T,typename Compare>
RBNode<T>* RBTree<T,Compare>::search(RBNode<T> *pivot)
{
		
		RBNode<T> *temp = root_;

		while(temp != NIL) {
			if(temp->value_ == pivot->value_)
				return temp;

			if(temp->value_ < pivot->value_)
				temp=temp->right_;

			else
				temp=temp->left_;
		}

		return nullptr;
}


template<typename T,typename Compare>
RBNode<T> * RBTree<T, Compare>::find_node(int n) {
	RBNode<T> * temp = root_;
	while (temp != NIL) 
	{
		//cout << "Here is find node" << endl;
		if (temp->value_> n ) 
		{
			if (temp->left_!=NIL)
			{
				temp = temp->left_;
			}
			else{
				break;
			}
			
		} 
		else if (n == temp->value_) 
		{
			return temp;
		} 
		else {
			if (temp->right_!=NIL)
			{
				temp = temp->right_;
			}
			else{
				break;
			}
		}
	
	}
	//cout << "Not found" << endl;
	return NIL;

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
RBNode<T>* RBTree<T, Compare>::tree_minimum(RBNode<T> *root)
{
	RBNode<T> *temp = root;
	while(temp -> left_ != NIL) {
		temp = temp->left_;
	}
	return temp;
} 


template<typename T,typename Compare>
void RBTree<T, Compare>::delete_fixup(RBNode<T> *x)
{
	RBNode<T>* w;
	while(x != root_ && x->color_ == BLACK && x != NIL) {
		if(x = x->parent_->left_) {
			w = x->parent_->right_;
			if(w->color_ == RED) {
				w->color_ = BLACK;
				x->parent_->color_ = RED;
				rotate_left(x->parent_);
				w = x->parent_->right_;
			}

			if(w->left_->color_ == BLACK && w->right_->color_ == BLACK) {
				w->color_ = RED;
				x = x->parent_;
			}

			else {
				if(w->right_->color_ == BLACK) {
					w->left_->color_ = BLACK;
					w->color_ = RED;
					rotate_right(w);
					w = x->parent_->right_;
				}
				w->color_ = x->parent_->color_;
				x->parent_->color_ = BLACK;
				w->right_->color_ = BLACK;
				rotate_left(x->parent_);
				x = root_;
			}
		}

		else {
			w = x->parent_->left_;
			if(w->color_ == RED) {
				w->color_ = BLACK;
				x->parent_->color_ = RED;
				rotate_right(x->parent_);
				w = x->parent_->left_;
			}

			if(w->right_->color_ == BLACK && w->left_->color_ == BLACK) {
				w->color_ = RED;
				x = x->parent_;
			}

			else {
				if(w->left_->color_ == BLACK) {
					w->right_->color_ = BLACK;
					w->color_ = RED;
					rotate_left(w);
					w = x->parent_->left_;
				}
				w->color_ = x->parent_->color_;
				x->parent_->color_ = BLACK;
				w->left_->color_ = BLACK;
				rotate_right(x->parent_);
				x = root_;
			}
		}
	}
	x->color_ = BLACK;
}


template<typename T,typename Compare>
void RBTree<T, Compare>::delete_node(RBNode<T> *z)
{
	RBNode<T> *x;
	RBNode<T> *y = z;
	Color y_original_color = y->color_;
	if(z->left_ == NIL) {
		x = z->right_;
		rb_transplant(z, z->right_);
	}

	else if(z->right_ == NIL) {
		x = z->left_;
		rb_transplant(z, z->left_);
	}

	else {
		y = tree_minimum(z->right_);
		y_original_color = y->color_;
		x = y->right_;

		if(y->parent_ == z)
			x->parent_ == y;

		else {
			rb_transplant(y, y->right_);
			y->right_ = z->right_;
			y->right_->parent_ = y;
		}
		rb_transplant(z, y);
		y->left_ = z->left_;
		y->left_->parent_ = y;
		y->color_ = z->color_;
	}

	if(y_original_color == BLACK)
		delete_fixup(x);
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

#if 0 // TO BE REMOVED.
template<typename T>
void RBTree<T>::post_successor()
{
	cout << "Post order successor :" << endl;
	postorder_successor(this->begin());
}

template<typename T>
void RBTree<T>::postorder_successor(RBTree<T>::Iterator y)
{
	if(y==nullptr)
	{
		return;
						// Logic not right!	
	}	
	postorder_successor(++y);
	//postorder_successor(y++);
	
	#if 1
	if(y!= nullptr)
	{
		cout << y ;
		
		//delete(&(*y));
		//delete (*y).left_;
		//delete (*y).right_;
				
	}
	#endif
	//cout << y << endl;
}
#endif 
#endif