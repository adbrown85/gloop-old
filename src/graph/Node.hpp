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
#include "Text.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Basic element of the scene graph.
 */
class Node {
public:
	typedef vector<Node*>::iterator iterator;
	Node();
	virtual ~Node() {};
	void addChild(Node *child);
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
	virtual bool areChildrenAssociatedAfter() const;
	virtual bool areChildrenFinalizedAfter() const;
	virtual void associate() {}
	virtual void associateAfter() {}
	iterator begin();
	static bool compare(Node *A, Node *B);
	static void destroy(Node *node);
	iterator end();
	virtual void finalize() {}
	virtual void finalizeAfter() {}
	static Node* findRoot(Node *node);
	vector<Node*> getChildren() const;
	string getClassName() const;
	float getDepth() const;
	Node* getParent() const;
	bool hasChildren() const;
	virtual bool isSealed() const;
	friend ostream& operator<<(ostream &stream, const Node &node);
	void setDepth(float depth);
	virtual string toString() const;
protected:
	float depth;
	Node *parent;
	vector<Node*> children;
};


inline bool Node::areChildrenAssociatedAfter() const {return true;}
inline bool Node::areChildrenDestroyable() const {return true;}
inline bool Node::areChildrenFinalizedAfter() const {return true;}
inline bool Node::areChildrenPrintable() const {return true;}
inline Node::iterator Node::begin() {return children.begin();}
inline Node::iterator Node::end() {return children.end();}
inline vector<Node*> Node::getChildren() const {return children;}
inline float Node::getDepth() const {return depth;}
inline Node* Node::getParent() const {return parent;}
inline bool Node::hasChildren() const {return !children.empty();}
inline bool Node::isSealed() const {return false;}
inline void Node::setDepth(float depth) {this->depth = depth;}


#endif
