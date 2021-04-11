#ifndef RB_NODE_H
#define RB_NODE_H

enum Color { Red, Black };

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
	/*
	 * 1. Define ctor.
	 * 2. Define setters and getters too? (so code looks a bit cleaner)
	 */		
};

#endif
