/*
 * Transformation.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transformation.hpp"


/** Adds a modify listener to this node. */
void Transformation::addListener(NodeListener *listener) {
	
	notifier.addListener(listener, NodeEvent::MODIFY);
}


/** Finds all the transforms above a node. */
void Transformation::findAll(Node *node, list<Transformation*> &L) {
	
	Transformation* transform;
	
	// Find all the transforms above the node
	L.clear();
	while (node != NULL) {
		transform = dynamic_cast<Transformation*>(node);
		if (transform != NULL) {
			L.push_front(transform);
		}
		node = node->getParent();
	}
}


/** Fires a modify event. */
void Transformation::fireEvent() {
	
	notifier.fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}

