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

	// Note: incrementing follows standard pre-order traversal
	Iterator& operator++();		// pre-increment
	Iterator operator++(int);	// post-increment
	RBNode<T> operator*();		// dereference
	bool operator==(const Iterator& rhs) const;	// equality
	bool operator!=(const Iterator& rhs) const;	// inequality
	void display(std::ostream& os = std::cout) const;

	friend ostream& operator<<(ostream& os, const Iterator& iterator)
	{
		iterator.display(os);
		return os;
	}

};


template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator& RBTree<T, Compare>::Iterator::operator++() // pre-increment
{
	p_it_ = preorder_successor(p_it_);
	return *this;
}

template<typename T, typename Compare>
typename RBTree<T, Compare>::Iterator RBTree<T, Compare>::Iterator::operator++(int) // post-increment
{
	Iterator temp(*this);
	p_it_ = preorder_successor(temp.p_it_);
	return temp;
}

template<typename T, typename Compare>
RBNode<T> RBTree<T, Compare>::Iterator::operator*()
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

#endif
