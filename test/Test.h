/*
 * Test.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_TEST_H
#define GLOOP_TEST_H
#include "gloop_common.h"
#include <glawt/GLAWTFactory.hpp>

class Test {
public:
	Test();
	virtual ~Test();
	virtual void setUp() {}
	virtual void tearDown() {}
protected:
	Window* getWindow() {return window;}
	Canvas* getCanvas() {return canvas;}
private:
	Window *window;
	Canvas *canvas;
};

inline Test::Test() {
	
    Window *window = GLAWTFactory::createWindow();
	Canvas *canvas = GLAWTFactory::createCanvas();
    window->add(canvas);
    window->show();
}

inline Test::~Test() {
	
	delete window;
	delete canvas;
}

#endif
