/*
 * MouseClickHelper.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <GL/glut.h>
#include <iostream>
#include <map>
#include "Binding.hpp"
#include "Command.hpp"
#include "Delegate.hpp"
#include "MouseClickHelper.hpp"
#include "Scene.hpp"
using namespace std;


void addBindings(multimap<int,Binding> &bins) {
	
	int key=GLUT_LEFT_BUTTON;
	
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      GLUT_ACTIVE_ALT,
	                                      Command::GRAB,
	                                      0.0f,
	                                      GLUT_DOWN)));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      GLUT_ACTIVE_ALT,
	                                      Command::MANIPULATE,
	                                      1.0f,
	                                      GLUT_DOWN)));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      0,
	                                      Command::CIRCLE_X,
	                                      1.0f,
	                                      'y')));
	bins.insert(pair<int,Binding>(key,
	                              Binding(GLUT_LEFT_BUTTON,
	                                      0,
	                                      Command::CIRCLE_Y,
	                                      1.0f,
	                                      'x')));
}


/**
 * Unit test for MouseClickHelper.
 */
int main(int argc,
         char *argv[]) {
	
	Delegate *delegate;
	MouseClickHelper *mch;
	Scene *scene;
	multimap<int,Binding> bins;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MouseClickHelper" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	scene = new Scene();
	delegate = new Delegate(scene);
	mch = new MouseClickHelper(delegate);
	addBindings(bins);
	
	// Test install
	glutInit(&argc, argv);
	mch->setBindings(bins);
	mch->install();
	mch->print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "MouseClickHelper" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

