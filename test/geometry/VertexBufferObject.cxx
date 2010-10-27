/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <gtkmm/main.h>
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"


/* CanvasListener. */
class FakeCanvasListener : public CanvasListener {
public:
	virtual void onCanvasInitEvent(Canvas &canvas) {}
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas) {}
	virtual void onCanvasButtonEvent(Canvas &canvas) {}
	virtual void onCanvasDragEvent(Canvas &canvas) {}
};

/* Handles a canvas display event. */
void FakeCanvasListener::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Test for VertexBufferObject. */
class VertexBufferObjectTest {
public:
	void setUp();
//	void testAllocate();
private:
	VertexBufferObject *vbo;
	Window *window;
	Canvas *canvas;
	FakeCanvasListener *listener;
};

/* Initializes the test. */
void VertexBufferObjectTest::setUp() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas(512, 512);
	listener = new FakeCanvasListener();
	canvas->addListener(listener);
	window->setTitle("VertexBufferObject Test");
	window->add(canvas);
	window->show();
	
	// Initialize
	vbo = new VertexBufferObject();
	ErrorChecker::check("After vertex buffer object.");
	list<VertexAttribute> attribs;
	attribs.push_back(VertexAttribute("MCVertex", 3));
	attribs.push_back(VertexAttribute("TexCoord0", 3));
	vbo->allocate(GL_STATIC_DRAW, 3, attribs);
	cerr << "Size: " << vbo->getSize() << endl;
	vbo->put(-0.5, +0.5, 0); // 1
	vbo->put( 0.0,  0.1, 0);
	vbo->put(-0.5, -0.5, 0); // 2
	vbo->put( 0.0,  0.0, 0);
	vbo->put(+0.5, +0.5, 0); // 3
	vbo->put( 1.0,  1.0, 0);
	vbo->put(0.0, 0.0, 0.0); // Should throw exception!!
	
	window->run();
}

/* Runs the test. */
int main(int argc, char **argv) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectTest test;
	
	try {
		test.setUp();
	} catch (BasicException &e) {
		cerr << e.getMessage() << endl;
	}
	
}
