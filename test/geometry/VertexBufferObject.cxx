/*
 * VertexBufferObject.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "VertexBufferObject.hpp"
#include "ErrorChecker.hpp"
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"


/** Unit test for VertexBufferObject. */
class VertexBufferObjectTest {
public:
	void setUp();
	void tearDown();
	void testAllocate();
	void testPut();
	void testFlush();
	void testDraw();
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

/** Ensures the VBO creates the correct size. */
void VertexBufferObjectTest::testAllocate() {
	
	VertexBufferObject *vbo;
	int param;
	
	vbo = new VertexBufferObject();
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->addAttribute("TexCoord0", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &param);
	assert(param == sizeof(float) * (3 + 3) * 3);
	
	ErrorChecker::assertNoError("testAllocate");
}

/** Ensures an exception will be thrown when put is exceeded. */
void VertexBufferObjectTest::testPut() {
	
	VertexBufferObject *vbo;
	
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
		return;
	}
	assert(false);
}

/** Ensures the data can be sent to the card. */
void VertexBufferObjectTest::testFlush() {
	
	VertexBufferObject *vbo;
	
	vbo = new VertexBufferObject();
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	
	vbo->put(-0.5, +0.5, 0);
	vbo->put(-0.5, -0.5, 0);
	vbo->put(+0.5, +0.5, 0);
	
	vbo->flush();
	ErrorChecker::assertNoError("testFlush");
}

class TestDrawListener : public CanvasListener {
public:
	TestDrawListener();
	virtual void onCanvasInitEvent(Canvas &canvas) {}
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas) {}
	virtual void onCanvasButtonEvent(Canvas &canvas) {}
	virtual void onCanvasDragEvent(Canvas &canvas) {}
private:
	VertexBufferObject *vbo;
	GLuint program;
	GLint pointLoc;
};

TestDrawListener::TestDrawListener() {
	
	GLuint vs, fs;
	
	vbo = new VertexBufferObject();
	vbo->bind();
	vbo->addAttribute("MCVertex", 3);
	vbo->allocate(GL_STATIC_DRAW, 3);
	vbo->put(-0.5, +0.5, 0);
	vbo->put(-0.5, -0.5, 0);
	vbo->put(+0.5, +0.5, 0);
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

void TestDrawListener::onCanvasDisplayEvent(Canvas &canvas) {
	
//	glViewport(0, 512, 0, 512);
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(program);
	vbo->bind();
	
	glEnableVertexAttribArray(pointLoc);
	glVertexAttribPointer(
			pointLoc, // index
			3,        // size
			GL_FLOAT, // type
			false,    // normalized
			0,        // stride
			0);       // offset
	
	ErrorChecker::assertNoError("After glVertexAttribPointer");
	
	glDrawArrays(
			GL_TRIANGLES, // mode
			0,            // first
			3);           // count
	
	vbo->unbind();
}

void VertexBufferObjectTest::testDraw() {
	
	canvas->addListener(new TestDrawListener());
	window->run();
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	VertexBufferObjectTest test;
	
	test.setUp();
	try {
		cout << "VertexBufferObjectTest::testAllocate" << endl;
		test.testAllocate();
		cout << "PASSED" << endl;
		cout << "VertexBufferObjectTest::testPut" << endl;
		test.testPut();
		cout << "PASSED" << endl;
		cout << "VertexBufferObjectTest::testFlush" << endl;
		test.testFlush();
		cout << "PASSED" << endl;
		cout << "VertexBufferObjectTest::testDraw" << endl;
		test.testDraw();
		cout << "PASSED" << endl;
	} catch (exception &e) {
		cerr << e.what() << endl;
		cout << "FAILED!" << endl;
		exit(1);
	}
	test.tearDown();
	cout << "PASSED ALL TESTS" << endl;
}
