#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"

using namespace std;

template <typename T>
class RBTree
{
	private:
		int tree_size;
		RBNode<T> *root;
		static RBNode<T> *NIL;

	public:

		class Iterator;
		Iterator begin();
		Iterator end();
};

template <typename T>
RBNode<T> *RBTree<T>::NIL = nullptr;

#endif
