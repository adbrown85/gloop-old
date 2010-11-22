/*
 * VertexBufferObjectDrawTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "VertexBufferObject.hpp"
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"


class VertexBufferObjectDrawTest : public Test {
public:
	VertexBufferObjectDrawTest();
	void testDraw();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
private:
	VertexBufferObject *vbo;
	GLuint program;
	GLint pointLoc;
};

VertexBufferObjectDrawTest::VertexBufferObjectDrawTest() {
	
	vbo = NULL;
	program = 0;
	pointLoc = -1;
}

void VertexBufferObjectDrawTest::testDraw() {
	
	getWindow()->run();
}

void VertexBufferObjectDrawTest::onCanvasInitEvent(Canvas &canvas) {
	
	GLuint vs, fs;
	
	vbo = new VertexBufferObject();
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->addAttribute("TexCoord0", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	vbo->put(-0.5, +0.5, 0); // 1
	vbo->put( 0.0,  1.0, 0);
	vbo->put(-0.5, -0.5, 0); // 2
	vbo->put( 0.0,  0.0, 0);
	vbo->put(+0.5, +0.5, 0); // 3
	vbo->put( 1.0,  1.0, 0);
	
	vbo->flush();
	vbo->unbind();
	
	vs = ShaderBuilder::build(GL_VERTEX_SHADER, "test/shader/basic.vert");
	fs = ShaderBuilder::build(GL_FRAGMENT_SHADER, "test/shader/basic.frag");
	program = ProgramBuilder::build(vs, fs);
	
	pointLoc = glGetAttribLocation(program, "MCVertex");
	if (pointLoc < 0) {
		throw BasicException("Location of MCVertex not found!");
	}
}

void VertexBufferObjectDrawTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(program);
	
	vbo->bind();
	
	glEnableVertexAttribArray(pointLoc);
	glVertexAttribPointer(
			pointLoc,         // index
			3,                // size
			GL_FLOAT,         // type
			false,            // normalized
			vbo->getStride(), // stride
			0);               // offset
	
	glDrawArrays(
			GL_TRIANGLES, // mode
			0,            // first
			3);           // count
	
	vbo->unbind();
}

#define HARNESS VertexBufferObjectDrawTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDraw)
RUN_TESTS

