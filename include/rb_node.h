#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { RED, BLACK };

template <typename T>
class RBNode
{
	private:
		T value_;
		RBNode *parent_;
		RBNode *left_;
		RBNode *right_;
		Color color_;
	public:
		RBNode() = default;

		RBNode(const T& value = 0, RBNode<T> *parent = nullptr, RBNode<T> *left= nullptr, RBNode<T> *right= nullptr, Color color = RED)
		: value_(value), left_(left), right_(right), parent_(parent), color_(color)
		{}

		T get_value() { return value_; }
		RBNode *get_parent() { return parent_; }
		RBNode *get_left() { return left_; }
		RBNode *get_right() { return right_; }
		Color get_color() { return color_; }

};

#endif
