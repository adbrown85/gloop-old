/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include <gtkmm/main.h>
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"


/** Unit test for VertexBufferObject. */
class VertexBufferObjectTest {
public:
	void setUp();
	void tearDown();
	void testPut();
private:
	Window *window;
	Canvas *canvas;
};

/** Create a window/canvas so we can call GL functions. */
void VertexBufferObjectTest::setUp() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas(512, 512);
	window->setTitle("VertexBufferObject Test");
	window->add(canvas);
	window->show();
}

/** Destroy the window/canvas. */
void VertexBufferObjectTest::tearDown() {

	delete window;
	delete canvas;
}

/** Ensures an exception will be thrown when put is exceeded. */
void VertexBufferObjectTest::testPut() {
	
	VertexBufferObject *vbo;
	
	cout << "VertexBufferObjectTest::testPut" << endl;
	
	vbo = new VertexBufferObject();
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->addAttribute("TexCoord0", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	vbo->put(-0.5, +0.5, 0); // 1
	vbo->put( 0.0,  0.1, 0);
	vbo->put(-0.5, -0.5, 0); // 2
	vbo->put( 0.0,  0.0, 0);
	vbo->put(+0.5, +0.5, 0); // 3
	vbo->put( 1.0,  1.0, 0);
	
	try {
		vbo->put(0.0, 0.0, 0.0);
	} catch (exception &e) {
		ErrorChecker::assertNoError("testPut");
		cout << "PASSED" << endl;
		return;
	}
	assert(false);
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectTest test;
	
	test.setUp();
	try {
		test.testPut();
	} catch (exception &e) {
		cerr << e.what() << endl;
		cout << "FAILED!" << endl;
		exit(1);
	}
	test.tearDown();
	cout << "PASSED ALL TESTS" << endl;
}
