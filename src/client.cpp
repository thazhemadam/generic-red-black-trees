#include <iostream>
#include "rb.h"

using namespace std;

struct temp {
	int x;
	int y;
	bool operator()(const temp& lhs, const temp& rhs) { return lhs.y < rhs.y; }
	friend std::ostream& operator<<(std::ostream& os, const temp& temp) {
		os << temp.y;
		return os;
	}
};

int main(void)
{
	
	RBTree<int> *tree = new RBTree<int>();

	// // RBTree<struct temp, struct temp> *tree = new RBTree<struct temp, struct temp>();
	// // temp,temp
	// #if 0 // Create a tree using Insert
	// 	// 11, 2, 14, 1, 15, 7, 5, 8, 4
	// 	#if 0
	// 	RBNode<int> *roots = new RBNode<int>(11);
	// 	RBNode<int> *l = new RBNode<int>(3);
	// 	RBNode<int> *ll = new RBNode<int>(1);
	// 	RBNode<int> *lr = new RBNode<int>(7);
	// 	RBNode<int> *lrl = new RBNode<int>(5);
	// 	RBNode<int> *lrr = new RBNode<int>(8);
	// 	RBNode<int> *r = new RBNode<int>(1);
	// 	RBNode<int> *rr = new RBNode<int>(15);
	// 	RBNode<int> *newNode = new RBNode<int>(4);


	// 	// RBTree<int>::Iterator it_roots = tree->insert(roots);
	// 	// RBTree<int>::Iterator it_l = tree->insert(l);
	// 	// RBTree<int>::Iterator it_r = tree->insert(r);
	// 	// RBTree<int>::Iterator it_ll = tree->insert(ll);
	// 	// RBTree<int>::Iterator it_lr = tree->insert(lr);
	// 	// RBTree<int>::Iterator it_rr = tree->insert(rr);
	// 	// RBTree<int>::Iterator it_lrl = tree->insert(lrl);
	// 	// RBTree<int>::Iterator it_lrr = tree->insert(lrr);
	// 	// RBTree<int>::Iterator it_new = tree->insert(newNode);
	// 	#endif
	// 	tree->insert(2);  	// 8	- 1	2
	// 	tree->insert(7); 	// 3	- 2	
	// 	tree->insert(8); 	// 2	- 3
	// 	tree->insert(1); 	// 9	- 4
	// 	tree->insert(9); 	// 1	- 5
	// 	tree->insert(0); 	// 10	- 6
	// 	tree->insert(4); 	// 6	- 7
	// 	tree->insert(5); 	// 5	- 8
	// 	tree->insert(3); 	// 7	- 9
	// 	tree->insert(6); 	// 4	- 10

		
	// 	// RBTree<int>::Iterator it_1 = tree->begin();
	// 	// cout << *tree << tree << endl;
	// 	// tree->display();
	// 	cout << *tree;
	// 	// RBTree<int> newtree = RBTree<int>(*tree);
	// 	// cout << newtree << &newtree<< endl;
	// 	#if 0 // Test for level-order successors


	// 	cout << *tree;
	// 	cout << "Levelorder successors!\n";
	// 	cout << it_lr;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, lr))) << "\n\n";
	// 	cout << it_l;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, l))) << "\n\n";
	// 	cout << it_roots;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, roots))) << "\n\n";
	// 	cout << it_ll;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, ll))) << "\n\n";
	// 	cout << it_lrl;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrl))) << "\n\n";
	// 	cout << it_lrr;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, lrr))) << "\n\n";
	// 	cout << it_r;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, r))) << "\n\n";
	// 	cout << it_rr;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, rr))) << "\n\n";
	// 	cout << it_new;
	// 	cout << (RBTree<int>::Iterator(levelorder_successor(lr, newNode))) << "\n\n";
	// 	cout << *tree <<"\n";
	// 	RBTree<int> newTree = RBTree<int>(*tree);
	// 	cout << "\n"<< newTree;
	// 	#endif

	// 	#if 0 // Test for pre-order successors
	// 	tree->print_preorder();
	// 	cout << "Pre-order successors!\n";
	// 	cout << it_lr;
	// 	cout << RBTree<int>::Iterator(preorder_successor(lr)) << "\n\n";
	// 	cout << it_l;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(l))) << "\n";
	// 	cout << it_roots;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(roots))) << "\n";
	// 	cout << it_ll;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(ll))) << "\n";
	// 	cout << it_lrl;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(lrl))) << "\n";
	// 	cout << it_lrr;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(lrr))) << "\n";
	// 	cout << it_r;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(r))) << "\n";
	// 	cout << it_rr;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(rr))) << "\n";
	// 	cout << it_new;
	// 	cout << (RBTree<int>::Iterator(preorder_successor(newNode))) << "\n";
	// 	cout << *tree <<"\n";
	// 	RBTree<int> newTree = RBTree<int>(*tree);
	// 	cout << "\n"<< newTree;

	// 	#endif

	// 	#if 0 // Test for post-order successors
	// 	tree->print_postorder();
	// 	cout << "Post-order successors!\n";
	// 	cout << it_lr;
	// 	cout << RBTree<int>::Iterator(postorder_successor(lr)) << "\n\n";
	// 	cout << it_l;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(l))) << "\n";
	// 	cout << it_roots;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(roots))) << "\n";
	// 	cout << it_ll;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(ll))) << "\n";
	// 	cout << it_lrl;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(lrl))) << "\n";
	// 	cout << it_lrr;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(lrr))) << "\n";
	// 	cout << it_r;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(r))) << "\n";
	// 	cout << it_rr;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(rr))) << "\n";
	// 	cout << it_new;
	// 	cout << (RBTree<int>::Iterator(postorder_successor(newNode))) << "\n";
	// 	cout << *tree <<"\n";
	// 	RBTree<int> newTree = RBTree<int>(*tree);
	// 	cout << "\n"<< newTree;

	// 	#endif
	// #endif


	// //#if 1
	// struct temp y1 = {5, 13}; // 5 < 13 T/F
	// struct temp y2 = {6, 12};
	// struct temp y3 = {7, 11};
	// struct temp y4 = {8, 10};
	// struct temp y5 = {9, 9};
	// struct temp y6 = {10, 8};
	// struct temp y7 = {11, 7};
	// struct temp y8 = {12, 6};
	// struct temp y9 = {13, 5};
	// #if 0
	// RBNode<struct temp> * ny1 =  new RBNode<struct temp>(y1);
	// RBNode<struct temp> * ny2 =  new RBNode<struct temp>(y2);
	// RBNode<struct temp> * ny3 =  new RBNode<struct temp>(y3);
	// RBNode<struct temp> * ny4 =  new RBNode<struct temp>(y4);
	// RBNode<struct temp> * ny5 =  new RBNode<struct temp>(y5);
	// RBNode<struct temp> * ny6 =  new RBNode<struct temp>(y6);
	// RBNode<struct temp> * ny7 =  new RBNode<struct temp>(y7);
	// RBNode<struct temp> * ny8 =  new RBNode<struct temp>(y8);
	// RBNode<struct temp> * ny9 =  new RBNode<struct temp>(y9);
	// #endif
	// #if 1
	RBNode<int> *ny1 = new RBNode<int>(11);
	RBNode<int> *ny2 = new RBNode<int>(3);
	RBNode<int> *ny3 = new RBNode<int>(1);
	RBNode<int> *ny4 = new RBNode<int>(7);
	RBNode<int> *ny5 = new RBNode<int>(5);
	RBNode<int> *ny6 = new RBNode<int>(8);
	RBNode<int> *ny7 = new RBNode<int>(12);
	RBNode<int> *ny8 = new RBNode<int>(15);
	RBNode<int> *ny9 = new RBNode<int>(4);
	tree->insert(ny1);
	tree->insert(ny2);
	tree->insert(ny3);
	tree->insert(ny4);
	tree->insert(ny5);
	tree->insert(ny6);
	tree->insert(ny7);
	tree->insert(ny8);
	tree->insert(ny9);	
	cout << *tree;
	// #endif
	//tree->delete_node(ny1);
	//tree->delete_node(ny2);
	//tree->delete_node(ny3); // check color
	//tree->delete_node(ny4);
	//tree->delete_node(ny5);
	//tree->delete_node(ny6);
	//tree->delete_node(ny7);
	//tree->delete_node(ny8);
	//tree->delete_node(ny9);
	
	cout << *tree;
	//tree->delete_node(ny6);
	//cout << *tree;

	//tree->delete_node(ny9);
	//cout << *tree;
	
	//tree->search(ny7);
	tree->search(12);
	tree->search(8);
	tree->search(7);
	tree->search(16);
	tree->search(15);

	return 0;
}