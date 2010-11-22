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
#include "ErrorChecker.hpp"
#include "../Test.h"

/* Fake BufferObject for exposing some methods. */
class FakeBufferObject : public BufferObject {
public:
	FakeBufferObject(GLenum type) : BufferObject(type) { }
	virtual void allocate(GLenum usage, GLsizei size);
};

/* Expose allocate method. */
inline void FakeBufferObject::allocate(GLenum usage, GLsizei size) {
	BufferObject::allocate(usage, size);
}

/** Unit test for BufferObject. */
class BufferObjectTest : public Test {
public:
	BufferObjectTest();
	virtual ~BufferObjectTest();
	void testConstructor();
	void testBind();
	void testAllocate();
private:
	Window *window;
	Canvas *canvas;
};

/** Create a window/canvas so we can call GL functions. */
BufferObjectTest::BufferObjectTest() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	window->add(canvas);
	window->show();
}

/** Destroy the window/canvas. */
BufferObjectTest::~BufferObjectTest() {
	
	delete window;
	delete canvas;
}

/** Ensure a BufferObject can be created. */
void BufferObjectTest::testConstructor() {
	
	BufferObject *bo;
	
//	cout << "BufferObjectTest::testConstructor" << endl;
	bo = new BufferObject(GL_ARRAY_BUFFER);
	assert(bo->getType() == GL_ARRAY_BUFFER);
	assert(bo->getHandle() != 0);
//	ErrorChecker::assertNoError("testConstructor");
//	cout << "PASSED" << endl;
}

/** Ensure BufferObject will be bound and unbound correctly. */
void BufferObjectTest::testBind() {
	
	BufferObject *bo;
	int handle;
	
//	cout << "BufferObjectTest::testConstructor" << endl;
	bo = new BufferObject(GL_ARRAY_BUFFER);
	bo->bind();
	assert(bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == bo->getHandle());
	bo->unbind();
	assert(!bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == 0);
//	ErrorChecker::assertNoError("testBind");
//	cout << "PASSED" << endl;
}

/** Ensure memory gets allocated correctly. */
void BufferObjectTest::testAllocate() {
	
	FakeBufferObject *bo;
	int param;
	
//	cout << "BufferObjectTest::testAllocate" << endl;
	bo = new FakeBufferObject(GL_ARRAY_BUFFER);
	bo->bind();
	bo->allocate(GL_STATIC_DRAW, 128);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &param);
	assert(param == GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &param);
	assert(param == 128);
	bo->unbind();
//	ErrorChecker::assertNoError("testAllocate");
//	cout << "PASSED" << endl;
}

/* Run the test. */
#define HARNESS BufferObjectTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testConstructor)
ADD_TEST(testBind)
ADD_TEST(testAllocate)
RUN_TESTS
