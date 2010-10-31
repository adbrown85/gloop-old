/*
 * BufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include <cassert>
#include "BufferObject.hpp"

class BufferObjectTest {
public:
	void setUp();
	void tearDown();
	void testConstructor();
	void testBind();
private:
	Window *window;
	Canvas *canvas;
};

void BufferObjectTest::setUp() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	
	window->setTitle("BufferObjectTest");
	window->add(canvas);
	window->show();
}

void BufferObjectTest::tearDown() {
	
	delete window;
	delete canvas;
}

void BufferObjectTest::testConstructor() {
	
	BufferObject *bo;
	
	cout << "BufferObjectTest::testConstructor" << endl;
	bo = new BufferObject(GL_ARRAY_BUFFER);
	assert(bo->getType() == GL_ARRAY_BUFFER);
	assert(bo->getHandle() != 0);
	cout << "PASSED" << endl;
}

void BufferObjectTest::testBind() {
	
	BufferObject *bo;
	int handle;
	
	cout << "BufferObjectTest::testConstructor" << endl;
	bo = new BufferObject(GL_ARRAY_BUFFER);
	bo->bind();
	assert(bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == bo->getHandle());
	bo->unbind();
	assert(!bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == 0);
	cout << "PASSED" << endl;
}

int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	BufferObjectTest test;
	
	test.setUp();
	test.testConstructor();
	test.testBind();
	test.tearDown();
	cout << "ALL TESTS PASSED" << endl;
}
