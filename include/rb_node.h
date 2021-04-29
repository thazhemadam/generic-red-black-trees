#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { BLACK, RED, DOUBLE_BLACK};

template <typename T>
class RBNode
{
public:
	T value_;
	RBNode *parent_;
	RBNode *left_;
	RBNode *right_;
	Color color_;

	// RBNode() = default;

	RBNode(const T& value = 0, RBNode<T> *parent = nullptr, RBNode<T> *left= nullptr, RBNode<T> *right= nullptr, Color color = RED)
	: value_(value), left_(left), right_(right), parent_(parent), color_(color)
	{}

	friend std::ostream& operator<<(std::ostream& os, const RBNode& node)
	{
		os << node.value_ << "\t";
		os << (node.color_ == 0 ? "black" : "red") <<"\n";
		os << node.parent_ << "\t";
		os << node.left_ << "\t";
		os << node.right_ << "\t";
		return os;
	}

};

#endif
