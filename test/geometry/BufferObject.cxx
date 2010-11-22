/*
 * BufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "BufferObject.hpp"
#include "ErrorChecker.hpp"

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
	void testConstructor();
	void testBind();
	void testAllocate();
};

/** Ensure a BufferObject can be created. */
void BufferObjectTest::testConstructor() {
	
	BufferObject *bo;
	
	bo = new BufferObject(GL_ARRAY_BUFFER);
	assert(bo->getType() == GL_ARRAY_BUFFER);
	assert(bo->getHandle() != 0);
}

/** Ensure BufferObject will be bound and unbound correctly. */
void BufferObjectTest::testBind() {
	
	BufferObject *bo;
	int handle;
	
	bo = new BufferObject(GL_ARRAY_BUFFER);
	bo->bind();
	assert(bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == bo->getHandle());
	bo->unbind();
	assert(!bo->isBound());
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &handle);
	assert(handle == 0);
}

/** Ensure memory gets allocated correctly. */
void BufferObjectTest::testAllocate() {
	
	FakeBufferObject *bo;
	int param;
	
	bo = new FakeBufferObject(GL_ARRAY_BUFFER);
	bo->bind();
	bo->allocate(GL_STATIC_DRAW, 128);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &param);
	assert(param == GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &param);
	assert(param == 128);
	bo->unbind();
}

/* Run the test. */
#define HARNESS BufferObjectTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testConstructor)
ADD_TEST(testBind)
ADD_TEST(testAllocate)
RUN_TESTS
