/*
 * ProgramBuilder.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include <glawt/GLAWTFactory.hpp>
#include "ProgramBuilder.hpp"
#include "ShaderBuilder.hpp"

/** Unit test for ProgramBuilder. */
class ProgramBuilderTest {
public:
	void setUp();
	void tearDown();
	void testBuild();
private:
	Canvas *canvas;
	Window *window;
};

/** Initializes the fixture. */
void ProgramBuilderTest::setUp() {
	
	canvas = GLAWTFactory::createCanvas();
	window = GLAWTFactory::createWindow();
	window->setTitle("ProgramBuilderTest");
	window->add(canvas);
	window->show();
}

/** Destroys the fixture. */
void ProgramBuilderTest::tearDown() {
	
	delete canvas;
	delete window;
}

/** Ensures a program can be linked. */
void ProgramBuilderTest::testBuild() {
	
	list<GLuint> shaders;
	GLuint program, shader;
	
	shader = ShaderBuilder::build(
			GL_FRAGMENT_SHADER,
			"test/shader/basic.frag");
	shaders.push_back(shader);
	shader = ShaderBuilder::build(
			GL_VERTEX_SHADER,
			"test/shader/basic.vert");
	shaders.push_back(shader);
	
	program = ProgramBuilder::build(shaders);
	assert(program > 0);
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	ProgramBuilderTest test;
	
	test.setUp();
	cout << "ProgramBuilderTest::testBuild()" << endl;
	test.testBuild();
	cout << "PASSED" << endl;
	cout << "PASSED ALL TESTS" << endl;
	test.tearDown();
}

