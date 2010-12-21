/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "VertexBuffer.hpp"
#include "VertexBufferBuilder.hpp"
#include "ErrorChecker.hpp"

/** Unit test for VertexBufferObject. */
class VertexBufferTest : public Test {
public:
	virtual void setUp();
	virtual void tearDown();
	void testAllocate();
	void testPut();
	void testFlush();
	void testStride();
	void testSize();
private:
	VertexBufferBuilder *builder;
	VertexBuffer *vbo;
};

/** Create a fresh VBO. */
void VertexBufferTest::setUp() {
	
	builder = new VertexBufferBuilder();
	builder->addAttribute("MCVertex", 3);
	builder->addAttribute("TexCoord0", 3);
	builder->setCapacity(3);
	builder->setUsage(GL_STATIC_DRAW);
	
	vbo = builder->toVertexBuffer();
	vbo->bind();
}

/** Destroy the VBO. */
void VertexBufferTest::tearDown() {
	
	vbo->unbind();
	delete vbo;
}

/** Ensures the VBO creates the correct size. */
void VertexBufferTest::testAllocate() {
	
	int param;
	
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &param);
	assert(param == (sizeof(float) * (3 + 3) * 3));
}

/** Ensures an exception will be thrown when put is exceeded. */
void VertexBufferTest::testPut() {
	
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
void VertexBufferTest::testFlush() {
	
	vbo->put(-0.5, +0.5, 0);
	vbo->put(-0.5, -0.5, 0);
	vbo->put(+0.5, +0.5, 0);
	
	vbo->flush();
}

/** Ensures the stride is allocated correctly. */
void VertexBufferTest::testStride() {
	
	assert(vbo->getStride() == 24);
}

void VertexBufferTest::testSize() {
	
	assert(vbo->getSize() == 72);
}

/* Run the test. */
#define HARNESS VertexBufferTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testAllocate)
ADD_TEST(testPut)
ADD_TEST(testFlush)
ADD_TEST(testStride)
ADD_TEST(testSize)
RUN_TESTS
