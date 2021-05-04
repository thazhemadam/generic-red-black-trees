#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { BLACK, RED };

template <typename O, typename Compare>
class RBTree;

template <typename T = int>
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

	RBNode(const T& value, RBNode<T> *parent = nullptr, RBNode<T> *left= nullptr, RBNode<T> *right= nullptr, Color color = RED)
	: value_(value), left_(left), right_(right), parent_(parent), color_(color)
	{}

	RBNode(const RBNode<T> &rhs);

// friends
	template <typename O, typename Compare>
	friend class RBTree;


	// friend functions
	friend std::ostream& operator<<(std::ostream& os, const RBNode& node)
	{
		os << node.value_ << "\t";
		os << (node.color_ == 0 ? "black" : "red") <<"\n";
		os << node.parent_ << "\t";
		os << node.left_ << "\t";
		os << node.right_ << "\n";
		return os;
	}

	template<typename O>
	friend void print_tree(std::ostream& os, const std::string& prefix, const RBNode<O> *node, bool is_left);

	template<typename O>
	friend void inorder(RBNode<O> *root);

	template<typename O>
	friend void preorder(RBNode<O> *root);

	template<typename O>
	friend void postorder(RBNode<O> *root);

	Color get_color();
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
Color RBNode<T>::get_color() {
	if (this == nullptr)
		return BLACK;

	return this->color_;
}

#endif