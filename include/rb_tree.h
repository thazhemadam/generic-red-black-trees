#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"
#include "utils.h"
#include <memory>
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

	RBNode<T>* tree_minimum(RBNode<T> *root) const;
	RBNode<T>* tree_maximum(RBNode<T> *root) const;
	// helpers for deletion
	void rb_transplant(RBNode<T> * u,RBNode<T> * v);
	void remove_fixup(RBNode<T> *x);

public:
	static unique_ptr<RBNode<T>> NIL;
	int tree_size_;

// special functions
	// constructors
	RBTree();				// empty tree
	RBTree(RBNode<T> node);			// tree with a root node
	RBTree(const RBTree<T, Compare> &rhs);	// copy constructor
	RBTree(RBTree<T, Compare> &&rhs); 	// move constructor
	RBTree<T,Compare>& operator=(const RBTree<T, Compare> &rhs);	// copy assignment
	RBTree<T,Compare>& operator=(RBTree<T, Compare> &&rhs);		//move assignment



	~RBTree();	// destructor

	// operator functions
	bool operator==(const RBTree<T, Compare> &rhs) const;	// equality
	bool operator!=(const RBTree<T, Compare> &rhs) const;	// inequality
	template<typename O, typename CO>
	friend std::ostream& operator<<(std::ostream& os, const RBTree<O, CO>& tree);

// Iterator class
	class Iterator;
	Iterator root() const
	{
		return Iterator(root_);
	}
	Iterator begin() const
	{
		return Iterator(tree_minimum(root_));
	}

	Iterator end() const
	{
		return Iterator(NIL.get());
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

	// delete tree
	void delete_tree();

//search functions
	Iterator search(T value) const;
	Iterator search(Iterator it) const;
	Iterator search(RBNode<T> *node) const;

	Iterator lower_bound(T value) const;
	Iterator upper_bound(T value) const;

// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	
// display functions
	void display(std::ostream& os = std::cout) const;
	void print_inorder() const;
	void print_preorder() const;
	void print_postorder() const;
};

// constructors
template <typename T, typename Compare>
unique_ptr<RBNode<T>> RBTree<T, Compare>::NIL = unique_ptr<RBNode<T>>(new RBNode<T>());


// constructors
template<typename T, typename Compare>
RBTree<T, Compare>::RBTree()
{
	root_ = NIL.get();
	tree_size_ = 0;
}


template<typename T, typename Compare>
RBTree<T, Compare>::RBTree(RBNode<T> node)
: root_(new RBNode<T>(node)), tree_size_(1)
{
	root_->color_ = BLACK;
}


template<typename T, typename Compare>
RBTree<T, Compare>::~RBTree()
{
	delete_tree();
}

// copy ctor
template<typename T, typename Compare>
RBTree<T, Compare>::RBTree(const RBTree<T, Compare> &rhs)
: tree_size_(rhs.tree_size_)
{
	#ifdef DEBUG
		cout << "Copy constructor was called";
	#endif
	if(rhs.root_ == NIL.get()) {
		root_ = NIL.get();
		return;
	}

	root_ = copy_tree(rhs.root_);
	root_->parent_ = NIL.get();
}


template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::copy_tree(RBNode<T> *root)
{
	RBNode<T> *new_left, *new_right, *new_node;
	if(root == NIL.get())
		return NIL.get();

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
RBTree<T, Compare>& RBTree<T,Compare>::operator=(const RBTree<T, Compare> &rhs)
{
	#ifdef DEBUG
		cout << "Copy assignment was called";
	#endif
	if(this != &rhs) {
		delete_tree();
		root_ = copy_tree(rhs.root_);
	}

	return *this;
}


//move ctor
template<typename T, typename Compare>
RBTree<T, Compare>::RBTree(RBTree<T, Compare> &&rhs)
: tree_size_(rhs.tree_size_)
{
	#ifdef DEBUG
		cout << "Move constructor was called";
	#endif
	root_ = rhs.root_;
	rhs.root_ = NIL.get();
	rhs.tree_size_ = 0;
}


//move assignment
template<typename T, typename Compare>
RBTree<T,Compare>& RBTree<T,Compare>::operator=(RBTree<T, Compare> &&rhs)
{
	#ifdef DEBUG
		cout << "Move assignment was called";
	#endif
	if(this != &rhs) {
		delete_tree();
		root_= rhs.root_;
		rhs.root_ = NIL.get();
		rhs.tree_size_ = 0;
	}

	return *this;
}


template<typename T, typename Compare>
bool RBTree<T, Compare>::operator==(const RBTree<T, Compare> &rhs) const
{
	if(tree_size_ != rhs.tree_size_)
		return false;

	Iterator it_lhs = begin();
	Iterator it_rhs = rhs.begin();

	while(it_lhs != end()) {
		if (*it_lhs != *it_rhs)
			return false;
		++it_lhs;
		++it_rhs;
	}
	return true;
}



template<typename T, typename Compare>
bool RBTree<T, Compare>::operator!=(const RBTree<T, Compare> &rhs) const
{
	if(tree_size_ != rhs.tree_size_)
		return true;

	Iterator it_lhs = begin();
	Iterator it_rhs = rhs.begin();

	while(it_lhs != end()) {
		if (*it_lhs != *it_rhs)
			return true;
		++it_lhs;
		++it_rhs;
	}
	return false;
}



template<typename T, typename Compare>
void RBTree<T, Compare>::rotate_left(RBNode<T> *pivot)
{
	#ifdef DEBUG
		
		cout << "\t-> Before left rotation on node " << pivot->value_ <<" - \n";
		display();
	#endif

	RBNode<T>* pivot_right = pivot->right_;

	if(pivot_right == NIL.get())
		return;

	pivot->right_= pivot_right->left_;

	if(pivot_right->left_ != NIL.get())
		pivot_right->left_->parent_ = pivot;

	pivot_right->parent_ = pivot->parent_;

	if(pivot->parent_ == NIL.get())
		root_ = pivot_right;

	else if(pivot == pivot->parent_->left_)
		pivot->parent_->left_ = pivot_right;

	else
		pivot->parent_->right_ = pivot_right;

	pivot_right->left_ = pivot;
	pivot->parent_ = pivot_right;
	
	#ifdef DEBUG
		
		cout << "\t-> After left rotation on node " << pivot->value_ <<" - \n";
		display();
	#endif
}


template<typename T, typename Compare>
void RBTree<T, Compare>::rotate_right(RBNode<T> *pivot)
{
	#ifdef DEBUG
		
		cout << "\t-> Before right rotation on node " << pivot->value_ <<" - \n";
		display();
	#endif

	RBNode<T>* pivot_left = pivot->left_;

	if(pivot_left == NIL.get())
		return;

	pivot->left_= pivot_left->right_;

	if(pivot_left->right_ != NIL.get())
		pivot_left->right_->parent_ = pivot;

	pivot_left->parent_ = pivot->parent_;

	if(pivot->parent_ == NIL.get())
		root_ = pivot_left;

	else if(pivot == pivot->parent_->right_)
		pivot->parent_->right_ = pivot_left;

	else
		pivot->parent_->left_ = pivot_left;

	pivot_left->right_ = pivot;
	pivot->parent_ = pivot_left;

	#ifdef DEBUG
		
		cout << "\t-> After right rotation on node " << pivot->value_ <<" - \n";
		display();
	#endif
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
	RBNode<T> *parent = NIL.get();
	RBNode<T> *temp = root_;

	while(temp != NIL.get()) {
		parent = temp;

		if(compare(node->value_ , temp->value_))
			temp = temp->left_;

		else
			temp = temp->right_;

	}

	node->parent_ = parent;

	if(parent == NIL.get())
		root_ = node;

	else if(compare(node->value_ , parent->value_))
		parent->left_ = node;

	else
		parent->right_ = node;

	node->left_ = NIL.get();
	node->right_ = NIL.get();
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
					#ifdef DEBUG
		
						cout << "\nLeft rotate called for insertion----\n";
						
					#endif
					rotate_left(node);
					#ifdef DEBUG
		
						cout << "Left rotate finished for insertion----\n";
						
					#endif
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				#ifdef DEBUG
		
						cout << "\nRight rotate called for insertion----\n";
						
					#endif
				rotate_right(node->parent_->parent_);
				#ifdef DEBUG
		
						cout << "Right rotate finished for insertion----\n";
						
				#endif
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
					#ifdef DEBUG
		
						cout << "\nRight rotate called for insertion----\n";
						
					#endif
					rotate_right(node);
					#ifdef DEBUG
		
						cout << "Right rotate finished for insertion----\n";
						
				#endif
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				#ifdef DEBUG
		
						cout << "\nLeft rotate called for insertion----\n";
						
				#endif
				rotate_left(node->parent_->parent_);
				#ifdef DEBUG
		
						cout << "Left rotate finished for insertion----\n";
						
				#endif
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
typename RBTree<T,Compare>::Iterator RBTree<T,Compare>::lower_bound(T value) const
{
	Iterator it = search(value);

	if(it != end()) {
		while(it.prev() != end() && *it.prev() == *it)
			--it;
	}

	return it;
}


template<typename T,typename Compare>
typename RBTree<T,Compare>::Iterator RBTree<T,Compare>::upper_bound(T value) const
{
	Iterator it = search(value);

	if(it != end()) {
		while(it.next() != end() && *it.next() == *it)
			++it;
	}

	return it;
}


template<typename T,typename Compare>
typename RBTree<T,Compare>::Iterator RBTree<T,Compare>::search(T value) const
{
	RBNode<T> node = RBNode<T>(value);
	return search(&node);
}


template<typename T,typename Compare>
typename RBTree<T,Compare>::Iterator RBTree<T,Compare>::search(RBTree<T,Compare>::Iterator it) const
{
	RBNode<T> *temp = &(*it);
	return search(temp);
}


template<typename T,typename Compare>
typename RBTree<T,Compare>::Iterator RBTree<T,Compare>::search(RBNode<T> *node) const
{

	RBNode<T> *temp = root_;

	while(temp != NIL.get()) {
		if(temp->value_ == node->value_)
			return Iterator(temp);

		if(compare(temp->value_, node->value_))
			temp=temp->right_;

		else
			temp=temp->left_;
	}

	return end();
}


template<typename T,typename Compare>
void RBTree<T, Compare>::rb_transplant(RBNode<T> *u,RBNode<T> *v)
{
	if(u->parent_ == NIL.get())
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
	Iterator it = search(value);

	if(it == nullptr) {
		cout << "\nNode with value : " << value << " does not exist in the RBTree.";
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
RBNode<T>* RBTree<T, Compare>::tree_minimum(RBNode<T> *root) const
{
	RBNode<T> *temp = root;
	while(temp -> left_ != NIL.get())
		temp = temp->left_;

	return temp;
} 

template<typename T,typename Compare>
RBNode<T>* RBTree<T, Compare>::tree_maximum(RBNode<T> *root) const
{
    RBNode<T> *temp = root;
    while(temp -> right_ != NIL.get())
        temp = temp->right_;

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
				#ifdef DEBUG
		
						cout << "\nLeft rotate called for deletion \n";
						
				#endif
				rotate_left(node->parent_);
				#ifdef DEBUG
		
						cout << "Left rotate finished for deletion \n";
						
				#endif
				sibling = node->parent_->right_;
			}

			if(!sibling->left_ && !sibling->right_) 	// sibling is a NIL node
			#ifdef DEBUG
		
						cout << "\tEncountered a left side sibling for node "<< node->value_ <<" which is NIL! Breaking out of while loop\n";
						
			#endif
				break;

			if(sibling->left_->color_ == BLACK && sibling->right_->color_ == BLACK) {
				sibling->color_ = RED;
				node = node->parent_;
			}

			else {
				if(sibling->right_->color_ == BLACK) {
					sibling->left_->color_ = BLACK;
					sibling->color_ = RED;
					#ifdef DEBUG
		
						cout << "\nRight rotate called for deletion \n";
						
					#endif
					rotate_right(sibling);
					#ifdef DEBUG
		
						cout << "Right rotate finished for deletion \n";
						
					#endif
					sibling = node->parent_->right_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = BLACK;
				sibling->right_->color_ = BLACK;
				#ifdef DEBUG
		
						cout << "\nLeft rotate called for deletion \n";
				#endif
				rotate_left(node->parent_);
				#ifdef DEBUG
		
						cout << "Left rotate finished for deletion \n";
						
				#endif
				node = root_;
			}
		}

		else {
			sibling = node->parent_->left_;
			if(sibling->color_ == RED) {
				sibling->color_ = BLACK;
				node->parent_->color_ = RED;
				#ifdef DEBUG
		
						cout << "\nRight rotate called for deletion \n";
						
				#endif
				rotate_right(node->parent_);
				#ifdef DEBUG
		
						cout << "Right rotate finished for deletion \n";
						
				#endif
				sibling = node->parent_->left_;
			}

			if(!sibling->left_ && !sibling->right_)	// sibling is a NIL node
			{
				#ifdef DEBUG
		
						cout << "\tEncountered a right side sibling for node "<< node->value_ <<" which is NIL! Breaking out of while loop\n";
						
				#endif
				break;
			}
				

			if(sibling->right_->color_ == BLACK && sibling->left_->color_ == BLACK) {
				sibling->color_ = RED;
				node = node->parent_;
			}

			else {
				if(sibling->left_->color_ == BLACK) {
					sibling->right_->color_ = BLACK;
					sibling->color_ = RED;
					#ifdef DEBUG
		
						cout << "\nLeft rotate called for deletion \n";
						
					#endif
					rotate_left(sibling);
					#ifdef DEBUG
		
						cout << "Left rotate finished for deletion \n";
						
				#endif
					sibling = node->parent_->left_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = BLACK;
				sibling->left_->color_ = BLACK;
				#ifdef DEBUG
		
						cout << "\nRight rotate called for deletion \n";
						
				#endif
				rotate_right(node->parent_);
				#ifdef DEBUG
		
						cout << "Right rotate called for deletion \n";
						
				#endif
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
	if(node->left_ == NIL.get()) {
		x = node->right_;
		rb_transplant(node, node->right_);
	}

	else if(node->right_ == NIL.get()) {
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
	{	
		#ifdef DEBUG
		
			cout << "\nNode "<< node->value_ <<" color before deletion was BLACK hence remove_fix called \n";
						
		#endif
		remove_fixup(x);
	}
	delete node;
	--tree_size_;
}


template<typename T, typename Compare>
void RBTree<T, Compare>::delete_tree()
{
	while(tree_size_ >= 1)
		remove(begin());

	root_ = NIL.get();
	tree_size_ = 0;
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