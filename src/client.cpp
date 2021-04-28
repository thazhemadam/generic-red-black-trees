#include <iostream>
#include "rb.h"

using namespace std;

int main(void)
{
	RBTree<int> *tree = new RBTree<int>();
	RBNode<int> *rootnode = new RBNode<int>(1);
	RBNode<int> *l = new RBNode<int>(2);
	RBNode<int> *r = new RBNode<int>(3);
	RBNode<int> *ll = new RBNode<int>(4);
	RBNode<int> *lr = new RBNode<int>(5);
	RBNode<int> *rl = new RBNode<int>(6);
	RBNode<int> *rr = new RBNode<int>(7);

	rootnode->left_ = l;
	rootnode->right_ = r;
	l->left_ = ll;
	l->right_ = lr;
	r->left_ = rl;
	r->right_ = rr;

	cout << tree->root_<<"\n";
	cout << rootnode <<"\n";
	tree-> root_ = rootnode;
	cout << "\n";
	cout << tree->root_<<"\n";
	cout << rootnode <<"\n";

	tree->inorder(tree->root_);


	return 0;
}
