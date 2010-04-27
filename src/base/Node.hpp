/*
 * Node.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
#include "Matrix.hpp"
using namespace std;


/**
 * @ingroup base
 * @brief
 *     Basic element of the scene graph.
 */
class Node {
	
	public :
		
		Node();
		void addChild(Node *child);
		virtual void associateTree();
		virtual void finalizeTree();
		virtual void print() const;
		virtual void printTree() const;
		virtual void sortByDepth(Matrix &matrix);
		virtual string toString() const;
		
		static void print(const Node *node);
		friend bool compare(Node *A, Node *B);
		
		vector<Node*> getChildren() const;
		string getClassName() const;
		float getDepth() const;
		Node* getParent() const;
		void setClassName(const string &className);
	
	protected :
		
		float depth;
		Node *parent;
		string className;
		vector<Node*> children;
		
		virtual void associate() {}
		virtual void computeDepth(Matrix &matrix);
		virtual void finalize() {}
		virtual void printTree(int level) const;
		virtual void sortByDepthBeg(Matrix &matrix) {}
		virtual void sortByDepthEnd(Matrix &matrix) {}
};


inline vector<Node*> Node::getChildren() const {return children;}
inline float Node::getDepth() const {return depth;}
inline string Node::getClassName() const {return className;}
inline Node* Node::getParent() const {return parent;}
inline void Node::setClassName(const string &className) {
	this->className = className;
}


#endif