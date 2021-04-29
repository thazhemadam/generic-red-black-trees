#include <iostream>
#include "rb.h"

using namespace std;

int main(void)
{
	RBTree<int> *tree = new RBTree<int>();

	// same example as CLRS
	RBNode<int> *lll = new RBNode<int>(2);
	RBNode<int> *lr = new RBNode<int>(6);
	RBNode<int> *rl = new RBNode<int>(9);
	RBNode<int> *rrll = new RBNode<int>(12);
	RBNode<int> *rrlr = new RBNode<int>(17);
	RBNode<int> *rrrrl = new RBNode<int>(20);

	RBNode<int> *rrrr = new RBNode<int>(22, nullptr, rrrrl);


	RBNode<int> *rrl = new RBNode<int>(14, nullptr, rrll, rrlr);
	RBNode<int> *rrr = new RBNode<int>(19, nullptr, nullptr, rrrr);

	RBNode<int> *ll = new RBNode<int>(3, nullptr, lll, nullptr);
	RBNode<int> *rr = new RBNode<int>(18, nullptr, rrl, rrr);

	RBNode<int> *l = new RBNode<int>(4, nullptr, ll, lr);
	RBNode<int> *r = new RBNode<int>(11, nullptr, rl, rr);

	RBNode<int> *rootnode = new RBNode<int>(7, nullptr, l, r);

	l->parent_ = rootnode;
	r->parent_ = rootnode;

	ll->parent_ = l;
	rr->parent_ = r;

	rrl->parent_ = rr;
	rrr->parent_ = rr;

	rrrr->parent_ = rrr;
	lll->parent_ = ll;
	lr->parent_ = l;
	rl->parent_ = r;
	rrll->parent_ = rrl;
	rrlr->parent_ = rrl;
	rrrrl->parent_ = rrrr;

	tree->root_ = rootnode;

	cout << *tree;
	tree->rotate_left(r);
	cout <<"\n";
	cout << *tree;
	return 0;
}
