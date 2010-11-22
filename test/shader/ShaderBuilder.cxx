/*
 * ShaderBuilder.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "../Test.h"
#include "ShaderBuilder.hpp"

/** Unit test for ShaderBuilder. */
class ShaderBuilderTest : public Test {
public:
	void testBuild();
};

/** Ensures a shader can be built properly from a file. */
void ShaderBuilderTest::testBuild() {
	
	int handle;
	GLchar buffer[1024];
	GLsizei length;
	stringstream stream;
	string line;
	vector<string> lines;
	
	// Build it
	handle = ShaderBuilder::build(
			GL_VERTEX_SHADER,
			"test/shader/basic.vert");
	assert(handle > 0);
	
	// Get the source
	glGetShaderSource(handle, 1024, &length, buffer);
	stream << buffer;
	getline(stream, line);
	lines.push_back(line);
	while (stream) {
		getline(stream, line);
		lines.push_back(line);
	}
	
	// Check the source
	assert(lines[0] == "#version 130");
	assert(lines[1] == "uniform mat4 MVPMatrix = mat4(1.0);");
	assert(lines[2] == "in vec4 MCVertex;");
	assert(lines[3] == "void main() {");
	assert(lines[4] == "    gl_Position = MVPMatrix * MCVertex;");
	assert(lines[5] == "}");
}

/* Run the test. */
#define HARNESS ShaderBuilderTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testBuild)
RUN_TESTS
