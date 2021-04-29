#ifndef RB_ITERATOR_H
#define RB_ITERATOR_H

#include "rb_tree.h"
#include "rb_node.h"

template<typename T>
class RBTree<T>::Iterator
{
	private:
		RBNode<T> *p_it_;

	public:
		Iterator(RBNode<T> *p_it) : p_it_(p_it) { }

		// Note: incrementing follows standard pre-order traversal
		Iterator& operator++();		// pre-increment
		Iterator operator++(int);	// post-increment
		RBNode<T> operator*();		// dereference
		bool operator==(const Iterator& rhs) const;	// equality
		bool operator!=(const Iterator& rhs) const;	// inequality
};


template<typename T>
typename RBTree<T>::Iterator& RBTree<T>::Iterator::operator++() // pre-increment
{
	++p_it_;
	return *this;
}

template<typename T>
typename RBTree<T>::Iterator RBTree<T>::Iterator::operator++(int) // post-increment
{
	Iterator temp(*this);
	++*this;
	return temp;
}

template<typename T>
RBNode<T> RBTree<T>::Iterator::operator*()
{
	return *p_it_;
}

template<typename T>
bool RBTree<T>::Iterator::operator==(const Iterator& rhs) const
{
	return p_it_ == rhs.p_it_;
}

template<typename T>
bool RBTree<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

#endif
