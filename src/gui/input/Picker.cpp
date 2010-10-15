/*
 * Picker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Picker.hpp"


Picker::Picker(Scene *scene, Canvas *canvas) : Traverser(scene) {
	
	// Initialize fields
	setCanvas(canvas);
	
	// Subscene
	try {
		openSubscene(PICKER_SUBSCENE);
		prepareSubscene();
		searchSubscene();
	} catch (Exception &ex) {
		glog << "[Picker] Unable to open '" << PICKER_SUBSCENE << "'" << endl;
		glog << "[Picker] Picking items with the mouse will not work." << endl;
		glog << "[Picker] Try reinstalling Gander." << endl;
	}
}


void Picker::addManipulators(list<Manipulator*> manips) {
	
	list<Manipulator*>::iterator it;
	
	for (it=manips.begin(); it!=manips.end(); ++it) {
		manipulators.push_back(*it);
	}
}


void Picker::onApplicable(Node *node, Applicable *applicable) {
	
	Transform *transform;
	
	// Ignore if nothing selectable
	if (!node->areChildrenSelectable())
		return;
	
	// Only apply transforms
	transform = dynamic_cast<Transform*>(node);
	if (transform != NULL) {
		Traverser::onApplicable(node, applicable);
	} else {
		traverseChildren(node);
	}
}


void Picker::onDrawable(Node *node, Drawable *drawable) {
	
	// Check if not visible
	if (!drawable->isVisible())
		return;
	
	// Check if not selectable
	if (!drawable->isSelectable())
		return;
	
	// Check if excluded
	if (drawable->isExcluded())
		return;
	
	// Do children first
	traverseChildren(node);
	
	// Then draw it
	itemIDUniform->setValue(drawable->getID());
	sourceIDUniform->setValue(drawable->getID());
	traverseSubscene();
	
	// Draw manipulators
	if (drawable->isSelected()) {
		renderHotspots(node);
	}
}


void Picker::renderHotspots(Node *node) {
	
	Transformable *transformable;
	list<Manipulator*>::iterator it;
	
	// Convert to transformable
	transformable = dynamic_cast<Transformable*>(node);
	
	// Set up
	State::setMode(MODEL_MODE);
	State::push();
	choose->setChoice("hotspot");
	
	// Draw a cube at each hotspot
	for (it=manipulators.begin(); it!=manipulators.end(); ++it) {
		State::loadIdentity();
		State::apply((*it)->getHotspotMatrix(transformable));
		itemIDUniform->setValue((*it)->getID());
		traverseSubscene();
	}
	
	// Reset
	choose->setChoice("cube");
	State::pop();
}


/** @return ID of item picked and shape it belongs to (0 if nothing). */
pair<GLuint,GLuint> Picker::pick(int x, int y) {
	
	Vector result;
	
	// Check if couldn't load file
	if (!isSubsceneOpened())
		return pair<GLuint,GLuint>(0,0);
	
	// Clear buffer
	choose->setChoice("clear");
	traverseSubscene();
	choose->setChoice("cube");
	
	// Traverse
	getCanvas()->getCamera()->apply();
	State::setMode(MODEL_MODE);
	State::loadIdentity();
	Traverser::start();
	
	// Read
	result = buffer->read(x, getCanvas()->getHeight()-y);
	return pair<GLuint,GLuint>(result[0],result[1]);
}


/** Finds all the required nodes from the subscene. */
void Picker::searchSubscene() {
	
	Node *node;
	
	// Find buffer node
	node = Scout<Renderbuffer>::search(getSubsceneRoot());
	buffer = dynamic_cast<Renderbuffer*>(node);
	if (buffer == NULL)
		throw Exception("[Picker] Could not find Renderbuffer node.");
	
	// Find choose node
	node = Scout<Choose>::search(getSubsceneRoot());
	choose = dynamic_cast<Choose*>(node);
	if (choose == NULL)
		throw Exception("[Picker] Could not find Choose node.");
	
	// Find ItemID uniform
	/* node = Nameable::search(getSubsceneRoot(), "ItemID"); */
	node = Scout<UniformInt>::search(getSubsceneRoot(), "ItemID");
	itemIDUniform = dynamic_cast<UniformInt*>(node);
	if (itemIDUniform == NULL)
		throw Exception("[Picker] Could not find 'ItemID' uniform.");
	
	// Find SourceID uniform
	/* node = Nameable::search(getSubsceneRoot(), "SourceID"); */
	node = Scout<UniformInt>::search(getSubsceneRoot(), "SourceID");
	sourceIDUniform = dynamic_cast<UniformInt*>(node);
	if (sourceIDUniform == NULL)
		throw Exception("[Picker] Could not find 'SourceID' uniform.");
}
