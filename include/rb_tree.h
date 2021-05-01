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
	RBTree();	// empty tree
	RBTree(RBNode<T> node);	// tree with a root node
	RBTree(const RBTree<T> &rhs);
	RBNode<T> *copy_tree(RBNode<T> *t);
	// operator function
	template<typename O>
	friend ostream& operator<<(ostream& os, const RBTree<O>& tree);

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

	

// utility functions
	inline bool is_empty() const { return tree_size_ == 0; }
	bool adjust_RBdelete(RBNode<T> *&node);
	
	void delete_node(int value_);
// display functions
	void print_inorder();
	void print_preorder();
	void print_postorder();
	void tree_insert(RBNode<T> *node);	// to be made private
	void deleteNode(RBNode<T>* &node);
private:
	int tree_size_;
	
	void adjust_delete(RBNode<T> * node, RBNode<T> * parent);
	void BSTreplace(RBNode<T> * u, RBNode<T> * v);
	
	RBNode<T>* find_min(RBNode<T>* node);
	RBNode<T>* find_node(int n);

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

// TODO - TEST THIS. Can be done only after copy constructor is created for RBNode.
template<typename T>
RBTree<T>::RBTree(RBNode<T> node)
: root_(new RBNode<T>(node)), tree_size_(1)
{}

// copy ctor
template<typename T>
RBTree<T>::RBTree(const RBTree<T> &rhs)
: tree_size_(rhs.tree_size_)
{
	if(rhs.root_ == nullptr) {
		root_ = nullptr;
		return;
	}

	root_ = copy_tree((rhs.root_));
}

template<typename T>
RBNode<T>* RBTree<T>::copy_tree(RBNode<T> *root)
{
	RBNode<T> *new_left, *new_right, *new_node;
	if(root == nullptr)
		return nullptr;

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

//Insertion
/*
 * tree_insert: inserts an RBNode into an RBTree, as though it were a regular tree.
		This only modifies the tree_size_ value.
 * @node:	pointer to the node that must be inserted
 */
template<typename T>
void RBTree<T>::tree_insert(RBNode<T> *node)
{
	RBNode<T> *y = nullptr;
	RBNode<T> *x = root_;

	while (x != NIL){
		y = x;

		if(node->value_ < x->value_)
			x = x->left_;
		else
			x = x->right_;
	}
	node->parent_ = y;

	if(y == nullptr)
		root_ = node;

	else {
		if(node->value_ < y->value_)
			y->left_ = node;
		else
			y-> right_ = node;
	}
	++tree_size_;
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
template<typename T>
typename RBTree<T>::Iterator RBTree<T>::insert(const T& value)
{
	// TODO: is this actually required? need to test things more first.
}

template<typename T>
typename RBTree<T>::Iterator RBTree<T>::insert(RBNode<T> *node)
{
	RBNode<T> *uncle;

	tree_insert(node);
	RBTree<T>::Iterator it = Iterator(node);

	while((node != root_) && (node->parent_->color_ == RED)) {

		if(node->parent_ == node->parent_->parent_->left_) {

			uncle = node->parent_->parent_->right_;

			if(uncle->color_ == RED) {
				node->parent_->color_ = BLACK;
				uncle->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if (node = node->parent_->right_) {
					node = node->parent_;
					rotate_left(node);
				}
				node->parent_->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				rotate_right(node->parent_->parent_);
			}
		}
		else {

			uncle = node->parent_->parent_->left_;

			if(uncle->color_ == RED) {
				node->parent_->color_ = BLACK;
				uncle->color_ = BLACK;
				node->parent_->parent_->color_ = RED;
				node = node->parent_->parent_;
			}
			else {
				if (node = node->parent_->left_) {
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
	return it;
}

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
	if(tree.root_ == nullptr) {
		os << "\nTree does not exist.\n";
		return os;
	}

	os << "_\n";
	print_tree(os, "", tree.root_, false);
	os << "\n";
	return os;
}

//deletion functions
template<typename T>
void RBTree<T>::adjust_delete(RBNode<T> * node , RBNode<T> * parent) {

    RBNode<T> * temp;

    while (node != root_ && node->getColor() == BLACK) {
	//cout << "check 1\n";
	cout << node << endl;
	
	// when node has parent
	if(node != NIL)
	{
	    	if (node == node->parent_->left_) {
			temp = node->parent_->right_;
			//cout << "check 2\n";
			if (temp->getColor() == RED) {
				  temp->setColor(BLACK);
				  node->parent_->setColor(RED);
				  //cout << "check 3\n";
				  rotate_left(node->parent_);
				  //cout << "check 4\n";
				  temp = node->parent_->right_;
			}

			if (temp->left_->getColor() == BLACK && temp->right_->getColor() == BLACK) {
				  temp->setColor(RED);
				  node = node->parent_;
			} else {

				  if (temp->right_->getColor() == BLACK) {
					    temp->left_->setColor(BLACK);
					    temp->setColor(RED);
					    rotate_right(temp);
					    temp = node->parent_->right_;
				  }

				  temp->setColor(node->parent_->color_);
				  node->parent_->setColor(BLACK);
				  temp->right_->setColor(BLACK);
				  rotate_left(node->parent_);
				  node = root_;
			}
	      } else {

			temp = node->parent_->left_;

			if (temp->getColor() == RED) {
				  temp->setColor(BLACK);
				  node->parent_->setColor(RED);
				  rotate_right(node->parent_);
				  temp = node->parent_->left_;
			}

			if (temp->right_->getColor() == BLACK && temp->right_->getColor() == BLACK) {
				  temp->setColor(RED);
				  node = node->parent_;
			} else {

				  if (temp->left_->getColor() == BLACK) {
					    temp->right_->setColor(BLACK);
					    temp->setColor(RED);
					    rotate_left(temp);
					    temp = node->parent_->left_;
				  }

				  temp->setColor(node->parent_->color_);
				  node->parent_->setColor(BLACK);
				  temp->left_->setColor(BLACK);
				  rotate_right(node->parent_);
				  node = root_;
			}
		  }
          }
          
          //when node doesn't have any node attributes
          else
          {
          	cout << "NIL nodes which has no parent value and color\n But are BLACK in color\n";
          	//cout << parent << endl;
          	//cout << node << endl;
          	
          	// if NIL is a left child
          	if (node == parent->left_) {
			temp = parent->right_;
			cout << "CHeck nil 2\n";
			
			//check sibiling
			if (temp->getColor() == RED) {
				  temp->setColor(BLACK);
				  parent->setColor(RED);
				  cout << "Check nil 3\n";
				  rotate_left(parent);
				  cout << "Check nil 4\n";
				  temp = parent->right_;
			}
			// both the siblings children are black
			if (temp->left_->getColor() == BLACK && temp->right_->getColor() == BLACK) {
				  temp->setColor(RED);
				  node = parent;
			} 
			else {
				// if any of the siblings children are red
				  if (temp->right_->getColor() == BLACK) {
					    temp->left_->setColor(BLACK);
					    temp->setColor(RED);
					    rotate_right(temp);
					    temp = parent->right_;
				  }

				  temp->setColor(parent->color_);
				  parent->setColor(BLACK);
				  temp->right_->setColor(BLACK);
				  rotate_left(parent);
				  node = root_;
			}
	      } 
	      // if NIL is a right child
	      else {

			temp = parent->left_;

			if (temp->getColor() == RED) {
				  temp->setColor(BLACK);
				  parent->setColor(RED);
				  rotate_right(parent);
				  temp = parent->left_;
			}

			if (temp->right_->getColor() == BLACK && temp->right_->getColor() == BLACK) {
				  temp->setColor(RED);
				  node = parent;
			} else {

				  if (temp->left_->getColor() == BLACK) {
					    temp->right_->setColor(BLACK);
					    temp->setColor(RED);
					    rotate_left(temp);
					    temp = parent->left_;
				  }

				  temp->setColor(parent->color_);
				  parent->setColor(BLACK);
				  temp->left_->setColor(BLACK);
				  rotate_right(parent);
				  node = root_;
			}
		  }
          	break;
          }
    }

    node->setColor(BLACK);
}
template<typename T>
void RBTree<T>::BSTreplace(RBNode<T> * u, RBNode<T> * v) {
  
    //cout << v <<"\n";
    
    if (u->parent_ == nullptr) {
	      root_ = v;
	} 
    else if (u == u->parent_->left_) {
	    
	      u->parent_->left_ = v;
	} 
    else {
    
    	  u->parent_->right_ = v;
    }
    
    
    if(v==NIL)
    {
    	u->parent_=NIL;
    }
    else
    {
    	v->parent_ = u->parent_;
    }
    
    //cout << u->parent_ <<"\n";
    //cout << "Replace check 5\n";
}
  
template<typename T>
RBNode<T>* RBTree<T>::find_node(int val) 
{
	RBNode<T>*  temp = root_;
	//cout << "find " << n <<" in " << temp->value_ << "\n";
	while (temp != NIL) 
	{
		if (temp->value_> val ) 
		{
			if (temp->left_!=NIL)
			{
				temp = temp->left_;
			}
			else{
				break;
			}
			
		} 
		else if (val == temp->value_) 
		{
			
			return temp;
			//cout << "find " << temp->value_ << "\n";
	
		} 
		else {
			if (temp->right_!=NIL)
			{
				temp = temp->right_;
			}
			else
			{
				break;
			}
		}
	
	}
	//cout << "find " << temp->value_ << "\n";
	return NIL;

}
template<typename T>
void RBTree<T>::deleteNode(RBNode<T>* &node) 
{
    if(node == NIL)
    {
    	return;
    }
    
    cout << "Deleting node with value --------" << node->value_ << endl;
    RBNode<T>* temp = node ;

    RBNode<T>* helper = NIL;
    
    RBNode<T>* parent = NIL;
    
    //bool isRight = false;
    Color old_temp_color = temp->color_;

    //cout << node->left_ << "\n";
    //cout << NIL << " NIl\n"; 
    
    if (node->left_ == NIL) 
    {
    		
	      helper = node->right_;
	      parent = node->parent_;
	      //cout << "Helperis right when left is NIL " << helper << endl;
	      //cout << "Parent when left is NIL " << parent << endl;
	      BSTreplace(node, node->right_);
    } 
    else if (node->right_ == NIL) 
    {
	      helper = node->left_;
	      parent = node->parent_;
	      //cout << "Helperis right when right is NIL " << helper << endl;
	      //cout << "Parent when right is NIL " << parent << endl;
	      BSTreplace(node, node->left_);
	      //isRight = true;
	      
    } 
    else 
    {
	      temp = find_min(node->right_);
	      //cout << "temp " << temp->value_ << endl;
	      //cout << "MINIMUM temp " << temp->value_ << "\n"; 
    		//cout << "node "<< node->right_->left_->left_ << endl;
	      old_temp_color = temp->color_;
	      helper = temp->right_;
	      parent = temp;
	      //cout << "MINIMUM temp " << temp->right_<< "\n"; 
	      
	      if (temp->parent_ == node) {
		      //helper->parent_ = temp;
			if(helper==NIL)
			{
				temp->right_=NIL;
			}
			else
			{
				helper->parent_ = temp;
			}
			cout << "helper" << "\n";
			//temp->right_=NIL;
		} 
	      else {
	      		BSTreplace(temp, temp->right_);
	      		cout << "helper" << "\n";
			//cout << "temp right " << temp->right_ << endl;
			//cout << "node right " << node->right_ << endl;
			if(temp->right_ == NIL)
			{
				temp->right_ = node->right_;
				//node->right_ = NIL;
			}
			else{
				temp->right_ = node->right_;
				temp->right_->parent_ = temp;
				}
	      }

	      BSTreplace(node, temp);
	      if(temp->left_ != NIL){
		      temp->left_ = node->left_;
		      temp->left_->parent_ = temp;
		      temp->color_ = node->color_;
	      }
	      else
	      {
	      	       temp->left_ = node->left_;
	              //node->left_ = NIL;
	      }
    }
    delete node;
     
    if (old_temp_color == BLACK) 
    {
    	      
	      adjust_delete(helper,parent);
    }
    //cout << "Test 2\n";
}
  
template<typename T>
RBNode<T>* RBTree<T>::find_min(RBNode<T>* node) {
    
    while (node->left_ != NIL) 
    {
      	  node = node->left_;
    }
    //cout << "Mini func " << node->value_ << "\n";
    return node;
  }

template<typename T>
void RBTree<T>::delete_node(int value_) {
	
	RBNode<T> * node = find_node(value_);
	//cout << node->value_ <<"\n";
	if(node!=NIL)
	{
		cout << " del " << node->value_ << "\n";
    		deleteNode(node);
    	}
    	else
    	{
    		cout << value_ << "  Not found !\n";
    	}
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