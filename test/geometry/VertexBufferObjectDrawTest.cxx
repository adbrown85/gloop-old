/*
 * VertexBufferObjectDrawTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "VertexBufferObject.hpp"
#include "VertexBufferObjectBuilder.hpp"
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
	
	runWindow();
}

void VertexBufferObjectDrawTest::onCanvasInitEvent(Canvas &canvas) {
	
	GLuint vertShader, fragShader;
	VertexBufferObjectBuilder builder;
	
	builder.addAttribute("MCVertex", 3);
	builder.addAttribute("TexCoord0", 3);
	builder.setUsage(GL_STATIC_DRAW);
	builder.setCapacity(3);
	
	vbo = builder.toVertexBuffer();
	vbo->bind();
	vbo->put(-0.5, +0.5, 0); // 1
	vbo->put( 0.0,  1.0, 0);
	vbo->put(-0.5, -0.5, 0); // 2
	vbo->put( 0.0,  0.0, 0);
	vbo->put(+0.5, +0.5, 0); // 3
	vbo->put( 1.0,  1.0, 0);
	vbo->flush();
	vbo->unbind();
	
	vertShader = ShaderBuilder::build("test/shader/basic.vert");
	fragShader = ShaderBuilder::build("test/shader/basic.frag");
	program = ProgramBuilder::build(vertShader, fragShader);
	
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

