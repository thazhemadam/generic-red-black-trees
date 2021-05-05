#ifndef RB_ITERATOR_H
#define RB_ITERATOR_H

#include "rb_tree.h"
#include "rb_node.h"

template<typename T, typename Compare>
class RBTree<T, Compare>::Iterator
{
private:
	RBNode<T> *p_it_;

public:

	Iterator() = default;
	Iterator(RBNode<T> *p_it) : p_it_(p_it) { }

	RBNode<T>& operator*();		// dereference

	// increment and decrement
	Iterator& operator++();
	Iterator operator++(int);
	Iterator& operator--();
	Iterator operator--(int);
	// comparison
	bool operator==(const Iterator& rhs) const;
	bool operator!=(const Iterator& rhs) const;
        bool operator>(const Iterator &) const;
	bool operator<(const Iterator &) const;
        bool operator<=(const Iterator &) const;
        bool operator>=(const Iterator &) const;

	void display(std::ostream& os = std::cout) const;

	friend ostream& operator<<(ostream& os, const Iterator& iterator)
	{
		iterator.display(os);
		return os;
	}

	RBNode<T>* levelorder_predecessor(const RBTree<T,Compare> *tree);
	RBNode<T>* levelorder_successor(const RBTree<T, Compare> *tree);
	RBNode<T>* preorder_predecessor(const RBTree<T,Compare> *tree);
	RBNode<T>* preorder_successor();
	RBNode<T>* postorder_predecessor(const RBTree<T,Compare> *tree);
	RBNode<T>* postorder_successor();
	RBNode<T>* inorder_successor();
	RBNode<T> * inorder_predecessor();
    //mew
    Iterator next();
    Iterator prev();
    bool hasnext();
    bool hasprev();
};


template<typename T, typename Compare>
RBNode<T>& RBTree<T, Compare>::Iterator::operator*()
{
	return *p_it_;
}


template<typename T, typename Compare>
bool RBTree<T, Compare>::Iterator::operator==(const Iterator& rhs) const
{
	return p_it_ == rhs.p_it_;
}


template<typename T, typename Compare>
bool RBTree<T, Compare>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}


template<typename T, typename Compare>
void RBTree<T, Compare>::Iterator::display(std::ostream& os) const
{
	if(p_it_ == nullptr) {
		os << "nullptr\n";
		return;
	}
	os << p_it_->value_ << "\t" << (p_it_->color_ == 0 ? "black" : "red")  << "\n";
}


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::Iterator::next() // next
{
    Iterator temp(*this);
    return temp.inorder_successor();
   
}

template<typename T, typename Compare>
bool RBTree<T, Compare>::Iterator::hasnext() 
{
    Iterator temp(*this);
    if(temp.inorder_successor()==nullptr)
    {
            return false;
    }
    return true;
}

template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::Iterator::prev() // prev
{
    Iterator temp(*this);
    return temp.inorder_predecessor();
}

template<typename T, typename Compare>
bool RBTree<T, Compare>::Iterator::hasprev() 
{
    Iterator temp(*this);
    if(temp.inorder_predecessor()==nullptr)
    {
        return false;
    }
    return true;
}

template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator& RBTree<T, Compare>::Iterator::operator++() // pre-increment
{
	p_it_ = inorder_successor();
	return *this;
}


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::Iterator::operator++(int) // post-increment
{
	Iterator temp(*this);
	p_it_ = temp.inorder_successor();
	return temp;
}


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator& RBTree<T, Compare>::Iterator::operator--() // pre-increment
{
	p_it_ = inorder_predecessor();
	return *this;
}


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::Iterator::operator--(int) // post-increment
{
	Iterator temp(*this);
	p_it_ = temp.inorder_predecessor();
	return temp;
}

template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::levelorder_predecessor(const RBTree<T,Compare> *tree)
{
    RBNode<T> *root=tree->root_;
    RBNode<T>* node= p_it_;
    if(root == nullptr)
        return nullptr;

    if(root == node)
        return nullptr;

    std::queue<RBNode<T>*> q;
    q.push(root);
    RBNode<T>* prev= nullptr;

    while(!q.empty()) {
        RBNode<T> *temp = q.front();
        q.pop();

        if(temp == node)
            break;

        else
            prev = temp;

        if(temp -> left_ != nullptr)
            q.push(temp->left_);

        if(temp -> right_ != nullptr)
            q.push(temp->right_);
    }

    return prev;
}

template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::levelorder_successor(const RBTree<T, Compare> *tree)
{
	RBNode<T> *root = tree->root_;
	RBNode<T> *node = p_it_;
	if(root == NIL.get())
		return nullptr;

	if(root == node) {
		if(root->left_ != NIL.get())
			return root->left_;

		else if(root->right_ != NIL.get())
			return root->left_;

		else
			return nullptr;
	}

	std::queue<RBNode<T>*> q;
	q.push(root);

	while(!q.empty()) {
		RBNode<T> *temp = q.front();
		q.pop();

		if(temp -> left_ != NIL.get())
			q.push(temp->left_);

		if(temp -> right_ != NIL.get())
			q.push(temp->right_);

		if(temp == node)
			break;
	}

	return q.front();
}


template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::preorder_predecessor(const RBTree<T,Compare> *tree)
{
    RBNode<T>* root=tree->root_;
    RBNode<T>* node= p_it_;
    RBNode<T>* parent = node->parent_;
    if (node == root)
        return nullptr;

    if (parent->left_ == nullptr || parent->left_ == node)
        return parent;

    RBNode<T>* current = parent->left_;
    while (current->right_ != nullptr)
        current = current->right_;

    return current;
}

template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::preorder_successor()
{
	RBNode<T> *node = p_it_;
	if(node == NIL.get())
		return nullptr;

	if(node->parent_ == nullptr)	// has no children, and is root.
		return nullptr;

	if (node->left_ && node->left_ !=  NIL.get())	// has left child.
		return node->left_;

	else if (node->right_ && node->right_ != NIL.get())	// has right child.
		return node->right_;

	RBNode<T> *parent = node->parent_;

	// leaf node. has an ancestor/is a node which is a left child + has a sibling.
	while(parent != nullptr) {
		if(parent->left_ == node && parent->right_ != NIL.get())
			return parent->right_;

		node = parent;
		parent = node->parent_;
	}

	// undefined case.
	return nullptr;
}


template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::postorder_predecessor(const RBTree<T,Compare> *tree)
{
   // RBNode<T>* parent = node->parent_;
    RBNode<T>* root=tree->root_;
    RBNode<T>* node= p_it_;
    RBNode<T>* temp = node->right_;
    RBNode<T> *current = node;
    RBNode<T> *parent = node->parent_;
    if (temp!=nullptr)
            return temp;
     
        // If right child does not exist, then
        // travel up (using parent pointers)
        // until we reach a node which is right
        // child of its parent
        while (parent != nullptr && parent->left_ == current) {
            current = current->parent_;
            parent = parent->parent_;
        }
     
        // If we reached root, then the given
        // node has no postorder predecessor
        if (parent == nullptr)
            return nullptr;
     
        return parent->left_;
}

template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::postorder_successor()
{
	RBNode<T> *node = p_it_;
	if(node == NIL.get())
		return nullptr;

	if(node->parent_ == NIL.get())	// node is root. undefined case.
		return nullptr;

	RBNode<T> *parent = node->parent_;

	// is the right child, or is a left child with no siblings
	if(node == parent->right_ || parent->right_ == NIL.get())
		return parent;

	// is the left child, with a right sibling
	RBNode<T> *temp = parent->right_;
	// until it is the next a leaf node. left-most leafnodes are given priority.
	while(temp->left_ != NIL.get() || temp->right_ != NIL.get()) {
		if(temp->left_ != NIL.get()){
			temp = temp->left_;
			continue;
		}

		else if(temp->right_ != NIL.get()){
			temp = temp->right_;
			continue;
		}
		
	}

	return temp;
}


template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::inorder_successor()
{
	RBNode<T>* node = p_it_;

	if(node == NIL.get())
		return nullptr;

	if(node->right_ != NIL.get()) {	// has a right child.
		RBNode<T> *temp = node->right_;
		while(temp->left_ != NIL.get())
			temp = temp->left_;
		
		return temp;
	}

	RBNode<T>* parent = node->parent_;

	// no right child. successor is the node whose left child
	while (parent != NIL.get() && parent->left_ != node) {
		node = node->parent_;
		parent = node->parent_;
	}

	return parent == NIL.get() ? nullptr : parent;
}

template<typename T, typename Compare>
RBNode<T>* RBTree<T, Compare>::Iterator::inorder_predecessor()
{
	RBNode<T>* node = p_it_;

	if(node == NIL.get())
		return nullptr;

	if(node->left_ != NIL.get()) {	// if it has a left child
		RBNode<T> *temp = node->left_;
		while(temp->right_ != NIL.get())
			temp = temp->right_;
		
		return temp;
	}

	// finding the ancestor whose right descendant is node
	RBNode<T>* parent = node->parent_;

	while (parent != NIL.get() && parent->right_ != node) {
		node = node->parent_;
		parent = node->parent_;
	}

	return parent == NIL.get() ? nullptr : parent;
}


#endif