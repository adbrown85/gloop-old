/*
 * ProgramBuilder.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "../Test.h"
#include "ProgramBuilder.hpp"
#include "ShaderBuilder.hpp"

/** Unit test for ProgramBuilder. */
class ProgramBuilderTest : public Test {
public:
	void testBuild();
};

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

/* Run the test. */
#define HARNESS ProgramBuilderTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testBuild)
RUN_TESTS

