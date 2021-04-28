#include <iostream>
#include "rb.h"

using namespace std;

int main(void)
{
	RBTree<int> *tree = new RBTree<int>();
	RBNode<int> *rootnode = new RBNode<int>(1);
	RBNode<int> *l = new RBNode<int>(2, nullptr, nullptr, nullptr, BLACK);
	RBNode<int> *r = new RBNode<int>(3);
	RBNode<int> *ll = new RBNode<int>(4);
	RBNode<int> *lr = new RBNode<int>(5);
	RBNode<int> *rl = new RBNode<int>(6);
	RBNode<int> *rr = new RBNode<int>(7);

	tree->root_ = rootnode;
	rootnode->left_ = l;
	rootnode->right_ = r;
	l->left_ = ll;
	l->right_ = lr;
	r->left_ = rl;
	r->right_ = rr;
	ll->left_ = RBTree<int>::NIL;
	lr->left_ = RBTree<int>::NIL;
	rl->left_ = RBTree<int>::NIL;
	rr->left_ = RBTree<int>::NIL;

	ll->right_ = RBTree<int>::NIL;
	lr->right_ = RBTree<int>::NIL;
	rl->right_ = RBTree<int>::NIL;
	rr->right_ = RBTree<int>::NIL;
	cout << *tree;

	return 0;
}
