#ifndef RB_ITERATOR_H
#define RB_ITERATOR_H

#include "rb_tree.h"
#include "rb_node.h"

class RBTree::Iterator
{
	private:
		RBNode *p_it_;

	public:
		Iterator(RBNode *p_it) : p_it_(p_it) { }
		Iterator& operator++();		// pre-increment
		Iterator operator++(int);	// post-increment
		RBNode operator*();		// dereference
		bool operator==(const Iterator& rhs) const;	// equality
		bool operator!=(const Iterator& rhs) const;	// inequality
};


RBTree::Iterator& RBTree::Iterator::operator++() // pre
{
	++p_it_;
	return *this;
}

RBTree::Iterator RBTree::Iterator::operator++(int) // post
{
	Iterator temp(*this);
	++*this;
	return temp;
}

RBNode RBTree::Iterator::operator*()
{
	return *p_it_;
}

bool RBTree::Iterator::operator==(const Iterator& rhs) const
{
	return p_it_ == rhs.p_it_;
}

bool RBTree::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

#endif
