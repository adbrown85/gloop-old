/*
 * Test.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_TEST_H
#define GLOOP_TEST_H
#include "gloop_common.h"
#include <cassert>
#include <glawt/GLAWTFactory.hpp>
#define TEST_EQUALS_TOLERANCE 0.00000001

class Test : public CanvasListener {
public:
	Test();
	virtual ~Test();
	virtual void init();
	virtual void setUp() {}
	virtual void tearDown() {}
	virtual void onCanvasInitEvent(Canvas &canvas) {}
	virtual void onCanvasDisplayEvent(Canvas &canvas) {}
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas) {}
	virtual void onCanvasDragEvent(Canvas &canvas) {}
protected:
	void assertEquals(float x, float y);
	void runWindow() {window->run();}
private:
	Window *window;
	Canvas *canvas;
};

Test::Test() {
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
}

Test::~Test() {
	delete window;
	delete canvas;
}

void Test::init() {
	canvas->addListener(this);
	window->setTitle("Test");
	window->add(canvas);
	window->show();
}

void Test::onCanvasKeyEvent(Canvas &canvas) {
	if (canvas.getState().combo.trigger == TOOLKIT_ESCAPE) {
		window->hide();
	}
}

void Test::assertEquals(float x, float y) {
	assert((x - y) < TEST_EQUALS_TOLERANCE
			&& (y - x) < TEST_EQUALS_TOLERANCE);
}

#endif
