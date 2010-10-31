/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <gtkmm/main.h>
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"


/** Unit test for VertexBufferObject. */
class VertexBufferObjectTest {
public:
	void testPut();
};

class TestPutListener : public CanvasListener {
public:
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas) {}
	virtual void onCanvasKeyEvent(Canvas &canvas) {}
	virtual void onCanvasButtonEvent(Canvas &canvas) {}
	virtual void onCanvasDragEvent(Canvas &canvas) {}
private:
	VertexBufferObject *vbo;
};

void TestPutListener::onCanvasInitEvent(Canvas &canvas) {
	
	vbo = new VertexBufferObject();
	ErrorChecker::check("After VertexBufferObject.");
	vbo->addAttribute("MCVertex", 3);
	vbo->addAttribute("TexCoord0", 3);
	vbo->bind();
	vbo->allocate(GL_STATIC_DRAW, 3);
	ErrorChecker::check("After allocate.");
	cerr << "Size: " << vbo->getSize() << endl;
	
	try {
		vbo->put(-0.5, +0.5, 0); // 1
		vbo->put( 0.0,  0.1, 0);
		vbo->put(-0.5, -0.5, 0); // 2
		vbo->put( 0.0,  0.0, 0);
		vbo->put(+0.5, +0.5, 0); // 3
		vbo->put( 1.0,  1.0, 0);
		vbo->put(0.0, 0.0, 0.0); // Should throw exception!!
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

/** Ensures an exception will be thrown when put is exceeded. */
void VertexBufferObjectTest::testPut() {
	
	Window *window;
	Canvas *canvas;
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas(512, 512);
	canvas->addListener(new TestPutListener());
	window->setTitle("VertexBufferObject Test");
	window->add(canvas);
	window->show();
	window->run();
	delete window;
	delete canvas;
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectTest test;
	
	try {
		test.testPut();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
}
