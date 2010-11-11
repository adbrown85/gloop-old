/*
 * ProgramAnalyzer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include <glawt/GLAWTFactory.hpp>
#include "ProgramAnalyzer.hpp"

/** Unit test for ProgramAnalyzer. */
class ProgramAnalyzerTest {
public:
	void setUpBeforeClass();
	void tearDownAfterClass();
	void testGetTypeName();
	void testListUniforms();
private:
	Window *window;
	Canvas *canvas;
};

/** Initializes the fixture. */
void ProgramAnalyzerTest::setUpBeforeClass() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	
	window->setTitle("ProgramAnalyzerTest");
	window->add(canvas);
	window->show();
}

/** Destroys the fixture. */
void ProgramAnalyzerTest::tearDownAfterClass() {
	
	delete window;
	delete canvas;
}

/** Ensures the human-readable description of uniform types is correct. */
void ProgramAnalyzerTest::testGetTypeName() {
	
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT) == "float");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_VEC2) == "vec2");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_VEC3) == "vec3");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_VEC4) == "vec4");
	assert(ProgramAnalyzer::getTypeName(GL_INT) == "int");
	assert(ProgramAnalyzer::getTypeName(GL_INT_VEC2) == "ivec2");
	assert(ProgramAnalyzer::getTypeName(GL_INT_VEC3) == "ivec3");
	assert(ProgramAnalyzer::getTypeName(GL_INT_VEC4) == "ivec4");
	assert(ProgramAnalyzer::getTypeName(GL_BOOL) == "bool");
	assert(ProgramAnalyzer::getTypeName(GL_BOOL_VEC2) == "bvec2");
	assert(ProgramAnalyzer::getTypeName(GL_BOOL_VEC3) == "bvec3");
	assert(ProgramAnalyzer::getTypeName(GL_BOOL_VEC4) == "bvec4");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_MAT2) == "mat2");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_MAT3) == "mat3");
	assert(ProgramAnalyzer::getTypeName(GL_FLOAT_MAT4) == "mat4");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_1D) == "sampler1D");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_2D) == "sampler2D");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_3D) == "sampler3D");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_CUBE) == "samplerCube");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_1D_SHADOW) == "sampler1DShadow");
	assert(ProgramAnalyzer::getTypeName(GL_SAMPLER_2D_SHADOW) == "sampler2DShadow");
}

/** Ensures information about uniforms can be retrieved from a program. */
void ProgramAnalyzerTest::testListUniforms() {
	
	map<string,UniformInfo> uniforms;
	GLenum type;
	GLuint vs, fs, program;
	
	vs = ShaderBuilder::build(GL_VERTEX_SHADER, "test/shader/basic.vert");
	fs = ShaderBuilder::build(GL_FRAGMENT_SHADER, "test/shader/basic.frag");
	program = ProgramBuilder::build(vs, fs);
	
	uniforms = ProgramAnalyzer::listUniforms(program);
	assert(uniforms["Color"].type == GL_FLOAT_VEC4);
	assert(uniforms["MVPMatrix"].type == GL_FLOAT_MAT4);
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	ProgramAnalyzerTest test;
	
	test.setUpBeforeClass();
	cout << "ProgramAnalyzer::testGetTypeName" << endl;
	test.testGetTypeName();
	cout << "PASSED" << endl;
	cout << "ProgramAnalyzer::testListUniforms" << endl;
	test.testListUniforms();
	cout << "PASSED" << endl;
	test.tearDownAfterClass();
	cout << "PASSED ALL TESTS" << endl;
	
	return 0;
}
