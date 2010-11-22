/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"

/** Unit test for VertexBufferObject. */
class VertexBufferObjectTest : public Test {
public:
	virtual void setUp();
	virtual void tearDown();
	void testAllocate();
	void testPut();
	void testFlush();
	void testStride();
	void testSize();
private:
	VertexBufferObject *vbo;
};

/** Create a fresh VBO. */
void VertexBufferObjectTest::setUp() {
	
	vbo = new VertexBufferObject();
	vbo->bind();
}

/** Destroy the VBO. */
void VertexBufferObjectTest::tearDown() {
	
	vbo->unbind();
	delete vbo;
}

/** Ensures the VBO creates the correct size. */
void VertexBufferObjectTest::testAllocate() {
	
	int param;
	
	vbo->addAttribute("MCVertex", 3);
	vbo->addAttribute("TexCoord0", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &param);
	assert(param == sizeof(float) * (3 + 3) * 3);
}

/** Ensures an exception will be thrown when put is exceeded. */
void VertexBufferObjectTest::testPut() {
	
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
		return;
	}
	assert(false);
}

/** Ensures the data can be sent to the card. */
void VertexBufferObjectTest::testFlush() {
	
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	vbo->put(-0.5, +0.5, 0);
	vbo->put(-0.5, -0.5, 0);
	vbo->put(+0.5, +0.5, 0);
	
	vbo->flush();
}

/** Ensures the stride is allocated correctly. */
void VertexBufferObjectTest::testStride() {
	
	vbo->addAttribute("MCVertex", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	assert(vbo->getStride() == 0);
}

void VertexBufferObjectTest::testSize() {
	
	vbo->addAttribute("MCVertex", 3);
	vbo->allocate(GL_STATIC_DRAW, 4);
	
	assert(vbo->getSize() == 48);
}

/* Run the test. */
#define HARNESS VertexBufferObjectTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testAllocate)
ADD_TEST(testPut)
ADD_TEST(testFlush)
ADD_TEST(testStride)
ADD_TEST(testSize)
RUN_TESTS
