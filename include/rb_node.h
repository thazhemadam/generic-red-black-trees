#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { RED, BLACK };

template <typename T>
class RBNode
{
	private:
		int value_;
		RBNode *parent_;
		RBNode *left_;
		RBNode *right_;
		Color color_;
	public:
		RBNode() = default;
		RBNode(const T& value) :  value_(value), left_(nullptr), right_(nullptr), parent_(nullptr), color_(RED)
		{}
		RBNode(const T& value, RBNode<T> *left_node, RBNode<T> *right_node, RBNode<T> *parent_node, Color color)
		: value_(value), left_(left_node), right_(right_node), parent_(parent_node), color_(color)
		{}

	/*
	 * 1. Define ctor.
	 * 2. Define setters and getters too? (so code looks a bit cleaner)
	 */		
};

#endif
