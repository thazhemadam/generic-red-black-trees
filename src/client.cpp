#include <iostream>
#include "rb.h"
#include <algorithm>

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
	// RBTree<int> *tree = new RBTree<int>();
	// RBTree<int> tree1;
	// RBTree<struct temp, struct temp> *tree_user = new RBTree<struct temp, struct temp>();
	// #if 1 // tree creation -pointer
	// RBNode<int> *ny11 = new RBNode<int>(11);
	// RBNode<int> *ny3 = new RBNode<int>(3);
	// RBNode<int> *ny1 = new RBNode<int>(1);
	// RBNode<int> *ny7 = new RBNode<int>(7);
	// RBNode<int> *ny5 = new RBNode<int>(5);
	// RBNode<int> *ny8 = new RBNode<int>(8);
	// RBNode<int> *ny12 = new RBNode<int>(12);
	// RBNode<int> *ny15 = new RBNode<int>(15);
	// RBNode<int> *ny4 = new RBNode<int>(4);
	// RBTree<int>::Iterator it_11 = tree->insert(ny11);
	// RBTree<int>::Iterator it_3 = tree->insert(ny3);
	// RBTree<int>::Iterator it_1 = tree->insert(ny1);
	// RBTree<int>::Iterator it_7 = tree->insert(ny7);
	// RBTree<int>::Iterator it_5 = tree->insert(ny5);
	// RBTree<int>::Iterator it_8 = tree->insert(ny8);
	// RBTree<int>::Iterator it_12 = tree->insert(ny12);
	// RBTree<int>::Iterator it_15 = tree->insert(ny15);
	// RBTree<int>::Iterator it_4 = tree->insert(ny4);
	// #endif

	// #if 1 // tree 1 creation - object
	// RBNode<int> *ny10_ = new RBNode<int>(10);
	// RBNode<int> *ny2_ = new RBNode<int>(2);
	// RBNode<int> *ny1_ = new RBNode<int>(1);
	// RBNode<int> *ny3_ = new RBNode<int>(3);
	// RBNode<int> *ny13_ = new RBNode<int>(13);
	// RBNode<int> *ny4_ = new RBNode<int>(4);
	// RBNode<int> *ny9_ = new RBNode<int>(9);
	// RBNode<int> *ny8_ = new RBNode<int>(8);
	// RBNode<int> *ny6_ = new RBNode<int>(6);
	// RBTree<int>::Iterator it_10_ = tree1.insert(ny10_);
	// RBTree<int>::Iterator it_2_ = tree1.insert(ny2_);
	// RBTree<int>::Iterator it_1_ = tree1.insert(ny1_);
	// RBTree<int>::Iterator it_3_ = tree1.insert(ny3_);
	// RBTree<int>::Iterator it_13_ = tree1.insert(ny13_);
	// RBTree<int>::Iterator it_4_ = tree1.insert(ny4_);
	// RBTree<int>::Iterator it_9_ = tree1.insert(ny9_);
	// RBTree<int>::Iterator it_8_ = tree1.insert(ny8_);
	// RBTree<int>::Iterator it_6_ = tree1.insert(ny6_);
	// #endif

	// #if 1 // user defined type tree creation
	// struct temp y1 = {5, 13}; // 5 < 13 T/F
	// struct temp y2 = {6, 12};
	// struct temp y3 = {7, 11};
	// struct temp y4 = {8, 10};
	// struct temp y5 = {9, 9};
	// struct temp y6 = {10, 8};
	// struct temp y7 = {11, 7};
	// struct temp y8 = {12, 6};
	// struct temp y9 = {13, 5};

	// RBNode<struct temp> *ny1_t = new RBNode<struct temp>(y1);
	// RBNode<struct temp> *ny2_t = new RBNode<struct temp>(y2);
	// RBNode<struct temp> *ny3_t = new RBNode<struct temp>(y3);
	// RBNode<struct temp> *ny4_t = new RBNode<struct temp>(y4);
	// RBNode<struct temp> *ny5_t = new RBNode<struct temp>(y5);
	// RBNode<struct temp> *ny6_t = new RBNode<struct temp>(y6);
	// RBNode<struct temp> *ny7_t = new RBNode<struct temp>(y7);
	// RBNode<struct temp> *ny8_t = new RBNode<struct temp>(y8);
	// RBNode<struct temp> *ny9_t = new RBNode<struct temp>(y9);

	// RBTree<struct temp,struct temp>::Iterator it_10_t = tree_user->insert(ny1_t);
	// RBTree<struct temp,struct temp>::Iterator it_2_t = tree_user->insert(ny2_t);
	// RBTree<struct temp,struct temp>::Iterator it_1_t = tree_user->insert(ny3_t);
	// RBTree<struct temp,struct temp>::Iterator it_3_t = tree_user->insert(ny4_t);
	// RBTree<struct temp,struct temp>::Iterator it_13_t = tree_user->insert(ny5_t);
	// RBTree<struct temp,struct temp>::Iterator it_4_t = tree_user->insert(ny6_t);
	// RBTree<struct temp,struct temp>::Iterator it_9_t = tree_user->insert(ny7_t);
	// RBTree<struct temp,struct temp>::Iterator it_8_t = tree_user->insert(ny8_t);
	// RBTree<struct temp,struct temp>::Iterator it_6_t = tree_user->insert(ny9_t);

	// cout << *tree_user;
	// #endif

	// RBTree<int> tree2 = std::move(tree1);
	// cout << tree2;
	// cout << "--\n";
	// cout << tree1;

	#if 1
	RBTree<int> *lb_tree = new RBTree<int>();
	lb_tree->insert(5);
	lb_tree->insert(5);
	lb_tree->insert(5);
	lb_tree->insert(7);
	RBNode<int> temp = RBNode<int>(4);
	RBTree<int>::Iterator it = lb_tree->insert(7);
	RBTree<int>::Iterator it1 = lb_tree->insert(&temp);

	RBTree<int>::Iterator it_start = lb_tree->begin();
	RBTree<int>::Iterator it_end = lb_tree->end();


	cout << "\n Tree: \n";
	cout << *lb_tree;
	cout << "\n Lower-Bound: \n";
	cout << *lb_tree->lower_bound(5);
	cout << "\n Upper-Bound: \n";
	cout << *lb_tree->upper_bound(7);

	// using generic find
	cout << "\n\nUsing generic find. \n";
	RBTree<int>::Iterator find_it = std::find(it_start, it_end, 7);
	cout << find_it; 

	#endif

	return 0;
}