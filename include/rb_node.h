#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { BLACK, RED };

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

	RBNode(const RBNode<T> &rhs);
	friend std::ostream& operator<<(std::ostream& os, const RBNode& node)
	{
		os << node.value_ << "\t";
		os << (node.color_ == 0 ? "black" : "red") <<"\n";
		os << node.parent_ << "\t";
		os << node.left_ << "\t";
		os << node.right_ << "\n";
		return os;
	}

	Color getColor();
	void setColor(Color color);
		
};

template<typename T>
RBNode<T>::RBNode(const RBNode<T> &rhs)
{
	parent_ = nullptr;
	left_ = nullptr;
	right_ = nullptr;
	value_ = rhs.value_;
	color_ = rhs.color_;
}

template<typename T>
Color RBNode<T>::getColor() {
	if (this == nullptr)
		return BLACK;

	return this->color_;
}

template<typename T>
void RBNode<T>::setColor( Color color) {
	if (this == nullptr)
		return;

	this->color_ = color;
}

#endif