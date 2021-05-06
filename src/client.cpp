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

	RBTree<int> tree1;

	RBTree<struct temp, struct temp> *tree_user = new RBTree<struct temp, struct temp>();

	// temp,temp
	#if 0 // Create a tree using Insert
		// 11, 2, 14, 1, 15, 7, 5, 8, 4
		#if 1
		RBNode<int> *roots = new RBNode<int>(11);
		RBNode<int> *l = new RBNode<int>(3);
		RBNode<int> *ll = new RBNode<int>(1);
		RBNode<int> *lr = new RBNode<int>(7);
		RBNode<int> *lrl = new RBNode<int>(5);
		RBNode<int> *lrr = new RBNode<int>(8);
		RBNode<int> *r = new RBNode<int>(1);
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
		#endif
		// tree->insert(2);  	// 8	- 1	2
		// tree->insert(7); 	// 3	- 2	
		// tree->insert(8); 	// 2	- 3
		// tree->insert(1); 	// 9	- 4
		// tree->insert(9); 	// 1	- 5
		// tree->insert(0); 	// 10	- 6
		// tree->insert(4); 	// 6	- 7
		// tree->insert(5); 	// 5	- 8
		// tree->insert(3); 	// 7	- 9
		// tree->insert(6); 	// 4	- 10

		
		cout << *tree;
		#if 0 // Test for level-order successors


		cout << *tree;
		cout << "\nLevelorder successors!\n";
		cout << it_lr;
		cout << it_lr.levelorder_successor(tree) << "\n\n";
		cout << it_l;
		cout << it_l.levelorder_successor(tree) << "\n\n";
		cout << it_roots;
		cout << it_roots.levelorder_successor(tree) << "\n\n";
		cout << it_ll;
		cout << it_ll.levelorder_successor(tree) << "\n\n";
		cout << it_lrl;
		cout << it_lrl.levelorder_successor(tree) << "\n\n";
		cout << it_lrr;
		cout << it_lrr.levelorder_successor(tree) << "\n\n";
		cout << it_r;
		cout << it_r.levelorder_successor(tree) << "\n\n";
		cout << it_rr;
		cout << it_rr.levelorder_successor(tree) << "\n\n";
		cout << it_new;
		cout << it_new.levelorder_successor(tree) << "\n\n";
		cout << *tree <<"\n";

		#endif

		#if 0 // Test for pre-order successors
		tree->print_preorder();
		cout << "\nPre-order successors!\n";
		cout << it_lr;
		cout << it_lr.preorder_successor() << "\n\n";
		cout << it_l;
		cout << it_l.preorder_successor() << "\n";
		cout << it_roots;
		cout << it_roots.preorder_successor() << "\n";
		cout << it_ll;
		cout << it_ll.preorder_successor() << "\n";
		cout << it_lrl;
		cout << it_lrl.preorder_successor() << "\n";
		cout << it_lrr;
		cout << it_lrr.preorder_successor() << "\n";
		cout << it_r;
		cout << it_r.preorder_successor() << "\n";
		cout << it_rr;
		cout << it_rr.preorder_successor() << "\n";
		cout << it_new;
		cout << it_new.preorder_successor() << "\n";
		cout << *tree <<"\n";
		// RBTree<int> newTree = RBTree<int>(*tree);
		// cout << "\n"<< newTree;

		#endif

		#if 0 // Test for post-order successors
		tree->print_postorder();
		// cout << *it_lr;
		cout << "\nPost-order successors!\n";
		cout << it_lr;
		cout << it_lr.postorder_successor() << "\n\n";
		cout << it_l;
		cout << it_l.postorder_successor() << "\n";
		cout << it_roots;
		cout << it_roots.postorder_successor() << "\n";
		cout << it_ll;
		cout << it_ll.postorder_successor() << "\n";
		cout << it_lrl;
		cout << it_lrl.postorder_successor() << "\n";
		cout << it_lrr;
		cout << it_lrr.postorder_successor() << "\n";
		cout << it_r;
		cout << it_r.postorder_successor() << "\n";
		cout << it_rr;
		cout << it_rr.postorder_successor() << "\n";
		cout << it_new;
		cout << it_new.postorder_successor() << "\n";
		cout << *tree <<"\n";
		#endif
	#endif


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

	
	#if 1 // tree creation
	RBNode<int> *ny11 = new RBNode<int>(11);
	RBNode<int> *ny3 = new RBNode<int>(3);
	RBNode<int> *ny1 = new RBNode<int>(1);
	RBNode<int> *ny7 = new RBNode<int>(7);
	RBNode<int> *ny5 = new RBNode<int>(5);
	RBNode<int> *ny8 = new RBNode<int>(8);
	RBNode<int> *ny12 = new RBNode<int>(12);
	RBNode<int> *ny15 = new RBNode<int>(15);
	RBNode<int> *ny4 = new RBNode<int>(4);
	RBTree<int>::Iterator it_11 = tree->insert(ny11);
	RBTree<int>::Iterator it_3 = tree->insert(ny3);
	RBTree<int>::Iterator it_1 = tree->insert(ny1);
	RBTree<int>::Iterator it_7 = tree->insert(ny7);
	RBTree<int>::Iterator it_5 = tree->insert(ny5);
	RBTree<int>::Iterator it_8 = tree->insert(ny8);
	RBTree<int>::Iterator it_12 = tree->insert(ny12);
	RBTree<int>::Iterator it_15 = tree->insert(ny15);
	RBTree<int>::Iterator it_4 = tree->insert(ny4);
	#endif
	

	
	#if 1 // tree 1 creation
	RBNode<int> *ny10_ = new RBNode<int>(10);
	RBNode<int> *ny2_ = new RBNode<int>(2);
	RBNode<int> *ny1_ = new RBNode<int>(1);
	RBNode<int> *ny3_ = new RBNode<int>(3);
	RBNode<int> *ny13_ = new RBNode<int>(13);
	RBNode<int> *ny4_ = new RBNode<int>(4);
	RBNode<int> *ny9_ = new RBNode<int>(9);
	RBNode<int> *ny8_ = new RBNode<int>(8);
	RBNode<int> *ny6_ = new RBNode<int>(6);
	RBTree<int>::Iterator it_10_ = tree1.insert(ny10_);
	RBTree<int>::Iterator it_2_ = tree1.insert(ny2_);
	RBTree<int>::Iterator it_1_ = tree1.insert(ny1_);
	RBTree<int>::Iterator it_3_ = tree1.insert(ny3_);
	RBTree<int>::Iterator it_13_ = tree1.insert(ny13_);
	RBTree<int>::Iterator it_4_ = tree1.insert(ny4_);
	RBTree<int>::Iterator it_9_ = tree1.insert(ny9_);
	RBTree<int>::Iterator it_8_ = tree1.insert(ny8_);
	RBTree<int>::Iterator it_6_ = tree1.insert(ny6_);
	#endif

	#if 0 // pre post inc/dec
	cout <<  it_11;
	cout << --it_12;
	cout << it_12--;
	cout << it_12++;
	cout << *tree;
	#endif

	#if 0 // search n delete
	cout << tree->search(it_3);
	tree->remove(4);
	tree->remove(3);
	cout << tree->search(it_3);

	tree->remove(42);
	tree->delete_tree();

	cout << *tree;
	#endif


	//cout << *tree1;
	//cout << *tree;
	
	//RBTree<int> *tree2 (tree); //copy ctr
	//tree = tree1; //copy assignment
	//tree = move(tree1); //move assignment
	RBTree<int> tree2 = std::move(tree1); //move ctr  // tree 2 dummy

	cout << tree1;
	cout << tree2;

	#if 0  // iterators
	cout <<  it_11.prev().prev();
	cout << it_11.hasprev(); 
	cout << it_11;
	
	cout <<  it_11.next();
	cout << it_11.hasnext();
	#endif

	#if 0 //BT is came! Not working
	cout << it_11.preorder_successor();
	cout << it_11.postorder_predecessor(tree);
	cout << it_11.preorder_predecessor(tree);
	#endif
	return 0;
}