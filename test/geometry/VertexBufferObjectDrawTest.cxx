/*
 * VertexBufferObjectDrawTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"


class VertexBufferObjectDrawTest : public CanvasListener {
public:
	VertexBufferObjectDrawTest();
	void testDraw();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas) {}
	virtual void onCanvasDragEvent(Canvas &canvas) {}
private:
	Window *window;
	Canvas *canvas;
	VertexBufferObject *vbo;
	GLuint program;
	GLint pointLoc;
};

VertexBufferObjectDrawTest::VertexBufferObjectDrawTest() {
	
	window = NULL;
	canvas = NULL;
	vbo = NULL;
	program = 0;
	pointLoc = -1;
}

void VertexBufferObjectDrawTest::testDraw() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	canvas->addListener(this);
	
	window->setTitle("VertexBufferObjectDrawTest");
	window->add(canvas);
	window->show();
	window->run();
	
	delete window;
	delete canvas;
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

void VertexBufferObjectDrawTest::onCanvasKeyEvent(Canvas &canvas) {
	
	if (canvas.getState().combo.trigger == TOOLKIT_ESCAPE) {
		window->hide();
	}
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectDrawTest test;
	
	cout << "VertexBufferObjectDrawTest::testDraw" << endl;
	test.testDraw();
	cout << "PASSED" << endl;
	cout << "PASSED ALL TESTS" << endl;
}
