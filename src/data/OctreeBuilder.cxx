/*
 * OctreeBuilder.cxx
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "OctreeBuilder.hpp"


class OctreeBuilderTester : public OctreeBuilder {
	
	public:
		
		OctreeBuilderTester(Dataset *dataset) : 
		                    OctreeBuilder(dataset) {}
		void print();
		void printOffsets();
		
		static void print(OctreeNode *node);
		static void indent(int times);
		static void printRecursive(OctreeNode *node,
		                           int depth,
		                           int maximumDepth);
};


void OctreeBuilderTester::indent(int times) {
	
	for (int i=0; i<times; ++i) {
		cout << "  ";
	}
}


void OctreeBuilderTester::print() {
	
	cout << toString() << endl;
}


void OctreeBuilderTester::print(OctreeNode *node) {
	
	cout << node->toString() << endl;
}


void OctreeBuilderTester::printOffsets() {
	
	for (int i=0; i<treeHeight+1; ++i) {
		cout << "  " << offsets[i] << endl;
	}
}


void OctreeBuilderTester::printRecursive(OctreeNode *node,
                                         int depth,
                                         int maximumDepth) {
	
	if (depth > maximumDepth)
		return;
	
	indent(depth);
	print(node);
	for (int i=0; i<8; ++i) {
		printRecursive(node->getChild(i), depth+1, maximumDepth);
	}
}


int main(int argc,
         char *argv[]) {
	
	Dataset *dataset;
	OctreeNode *root;
	OctreeBuilderTester *builder;
	
	// Basics
	dataset = new Dataset("../../input/bear.vlb");
	builder = new OctreeBuilderTester(dataset);
	builder->print();
	cout << "Offsets: " << endl;
	builder->printOffsets();
	
	// Build
	cout << "Building: " << endl;
	root = builder->build();
	OctreeBuilderTester::printRecursive(root, 0, 2);
	
	// Finish
	return 0;
}

