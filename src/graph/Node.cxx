/*
 * Node.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Node.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



/**
 * Unit test for Node.
 */
int main() {
	
	Node items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Build tree
	cout << "Building tree..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS-1; ++i)
		items[i].addChild(&items[i+1]);
	
	// Print tree
	cout << "Printing tree:" << endl;
	items[0].printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
