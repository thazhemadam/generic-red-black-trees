#include <iostream>
#include "rb.h"

using namespace std;

template<typename T>
class MyLess
{
public:
bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};


int main(void)
{
	RBTree<int, MyLess<int>> *tree = new RBTree<int, MyLess<int>>();

	#if 1 // Create a tree using Insert
		// 11, 2, 14, 1, 15, 7, 5, 8, 4
		#if 0
		RBNode<int> *roots = new RBNode<int>(11);
		RBNode<int> *l = new RBNode<int>(3);
		RBNode<int> *ll = new RBNode<int>(1);
		RBNode<int> *lr = new RBNode<int>(7);
		RBNode<int> *lrl = new RBNode<int>(5);
		RBNode<int> *lrr = new RBNode<int>(8);
		RBNode<int> *r = new RBNode<int>(1);
		RBNode<int> *rr = new RBNode<int>(15);
		RBNode<int> *newNode = new RBNode<int>(4);


		// RBTree<int>::Iterator it_roots = tree->insert(roots);
		// RBTree<int>::Iterator it_l = tree->insert(l);
		// RBTree<int>::Iterator it_r = tree->insert(r);
		// RBTree<int>::Iterator it_ll = tree->insert(ll);
		// RBTree<int>::Iterator it_lr = tree->insert(lr);
		// RBTree<int>::Iterator it_rr = tree->insert(rr);
		// RBTree<int>::Iterator it_lrl = tree->insert(lrl);
		// RBTree<int>::Iterator it_lrr = tree->insert(lrr);
		// RBTree<int>::Iterator it_new = tree->insert(newNode);
		#endif
		tree->insert(2);  	// 8	- 1	2
		tree->insert(7); 	// 3	- 2	
		tree->insert(8); 	// 2	- 3
		tree->insert(1); 	// 9	- 4
		tree->insert(9); 	// 1	- 5
		tree->insert(0); 	// 10	- 6
		tree->insert(4); 	// 6	- 7
		tree->insert(5); 	// 5	- 8
		tree->insert(3); 	// 7	- 9
		tree->insert(6); 	// 4	- 10

		
		// RBTree<int>::Iterator it_1 = tree->begin();
		// cout << *tree << tree << endl;
		// tree->display();
		cout << *tree;
		// RBTree<int> newtree = RBTree<int>(*tree);
		// cout << newtree << &newtree<< endl;
		#if 0 // Test for level-order successors


		cout << *tree;
		cout << "Levelorder successors!\n";
		cout << it_lr;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, lr))) << "\n\n";
		cout << it_l;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, l))) << "\n\n";
		cout << it_roots;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, roots))) << "\n\n";
		cout << it_ll;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, ll))) << "\n\n";
		cout << it_lrl;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrl))) << "\n\n";
		cout << it_lrr;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrr))) << "\n\n";
		cout << it_r;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, r))) << "\n\n";
		cout << it_rr;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, rr))) << "\n\n";
		cout << it_new;
		cout << (RBTree<int>::Iterator(levelorder_successor(lr, newNode))) << "\n\n";
		cout << *tree <<"\n";
		RBTree<int> newTree = RBTree<int>(*tree);
		cout << "\n"<< newTree;
		#endif

		#if 0 // Test for pre-order successors
		tree->print_preorder();
		cout << "Pre-order successors!\n";
		cout << it_lr;
		cout << RBTree<int>::Iterator(preorder_successor(lr)) << "\n\n";
		cout << it_l;
		cout << (RBTree<int>::Iterator(preorder_successor(l))) << "\n";
		cout << it_roots;
		cout << (RBTree<int>::Iterator(preorder_successor(roots))) << "\n";
		cout << it_ll;
		cout << (RBTree<int>::Iterator(preorder_successor(ll))) << "\n";
		cout << it_lrl;
		cout << (RBTree<int>::Iterator(preorder_successor(lrl))) << "\n";
		cout << it_lrr;
		cout << (RBTree<int>::Iterator(preorder_successor(lrr))) << "\n";
		cout << it_r;
		cout << (RBTree<int>::Iterator(preorder_successor(r))) << "\n";
		cout << it_rr;
		cout << (RBTree<int>::Iterator(preorder_successor(rr))) << "\n";
		cout << it_new;
		cout << (RBTree<int>::Iterator(preorder_successor(newNode))) << "\n";
		cout << *tree <<"\n";
		RBTree<int> newTree = RBTree<int>(*tree);
		cout << "\n"<< newTree;

		#endif

		#if 0 // Test for post-order successors
		tree->print_postorder();
		cout << "Post-order successors!\n";
		cout << it_lr;
		cout << RBTree<int>::Iterator(postorder_successor(lr)) << "\n\n";
		cout << it_l;
		cout << (RBTree<int>::Iterator(postorder_successor(l))) << "\n";
		cout << it_roots;
		cout << (RBTree<int>::Iterator(postorder_successor(roots))) << "\n";
		cout << it_ll;
		cout << (RBTree<int>::Iterator(postorder_successor(ll))) << "\n";
		cout << it_lrl;
		cout << (RBTree<int>::Iterator(postorder_successor(lrl))) << "\n";
		cout << it_lrr;
		cout << (RBTree<int>::Iterator(postorder_successor(lrr))) << "\n";
		cout << it_r;
		cout << (RBTree<int>::Iterator(postorder_successor(r))) << "\n";
		cout << it_rr;
		cout << (RBTree<int>::Iterator(postorder_successor(rr))) << "\n";
		cout << it_new;
		cout << (RBTree<int>::Iterator(postorder_successor(newNode))) << "\n";
		cout << *tree <<"\n";
		RBTree<int> newTree = RBTree<int>(*tree);
		cout << "\n"<< newTree;

		#endif
	#endif


	#if 1
	// tree->insert(54);

	#endif
	return 0;
}
