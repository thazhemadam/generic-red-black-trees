#include <iostream>
#include "rb.h"

using namespace std;

int main(void)
{
	RBTree<int> *tree = new RBTree<int>();

	#if 0
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
	#endif

	#if 1
		// 11, 2, 14, 1, 15, 7, 5, 8, 4
		RBNode<int> *roots = new RBNode<int>(11);
		RBNode<int> *l = new RBNode<int>(2);
		RBNode<int> *ll = new RBNode<int>(1);
		RBNode<int> *lr = new RBNode<int>(7);
		RBNode<int> *lrl = new RBNode<int>(5);
		RBNode<int> *lrr = new RBNode<int>(8);
		RBNode<int> *r = new RBNode<int>(14);
		RBNode<int> *rr = new RBNode<int>(15);
		RBNode<int> *newNode = new RBNode<int>(4);


		RBTree<int>::Iterator it_roots = tree->insert(roots);
		RBTree<int>::Iterator it_l = tree->insert(l);
		RBTree<int>::Iterator it_r = tree->insert(r);
		RBTree<int>::Iterator it_ll = tree->insert(ll);
		RBTree<int>::Iterator it_lr = tree->insert(lr);
		RBTree<int>::Iterator it_rr = tree->insert(rr);
		RBTree<int>::Iterator it_lrl = tree->insert(lrl);
		RBTree<int>::Iterator it_lrr = tree->insert(lrr);
		RBTree<int>::Iterator it_new = tree->insert(newNode);
		RBTree<int>::Iterator it_1 = tree->begin();

		// cout << *tree;
		// cout << "Levelorder successors!\n";
		// cout << *it_lr;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, lr))) << "\n\n";
		// cout << it_l;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, l))) << "\n\n";
		// cout << it_roots;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, roots))) << "\n\n";
		// cout << it_ll;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, ll))) << "\n\n";
		// cout << it_lrl;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrl))) << "\n\n";
		// cout << it_lrr;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrr))) << "\n\n";
		// cout << it_r;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, r))) << "\n\n";
		// cout << it_rr;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, rr))) << "\n\n";
		// cout << it_new;
		// cout << (RBTree<int>::Iterator(levelorder_successor(lr, newNode))) << "\n\n";
		cout << *tree <<"\n";
		RBTree<int> newTree = RBTree<int>(*tree);
		cout << "\n"<< newTree;

	#endif


	// cout << *tree;
	// tree->rotate_left(r);
	// cout <<"\n";
	// cout << *tree;
	
	// cout << "---- cloning -------\n";

	
	// RBTree<int> tree1(tree); // tree1 is an object
	
	
	//clone(tree,tree1); // clone function modified
	// cout << tree1;

	return 0;
}
