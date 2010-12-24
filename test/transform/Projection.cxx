/*
 * Projection.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Projection.hpp"
#include "ShaderFactory.hpp"
#include "ProgramBuilder.hpp"
#include "VertexBufferBuilder.hpp"
#include "ErrorChecker.hpp"


class ProjectionTest : public Test {
public:
	void testOrthographic();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
private:
	GLuint program;
	GLint mcVertexLocation;
	VertexBuffer *vbo;
};

void ProjectionTest::testOrthographic() {
	runWindow();
}

void ProjectionTest::onCanvasInitEvent(Canvas &canvas) {
	
	GLuint vShader, fShader;
	Matrix orthoMatrix;
	VertexBufferBuilder vbb;
	float orthoArray[16];
	GLint mvpMatrixLocation;
	
	// Make shader program
	vShader = ShaderFactory::create("test/shader/basic.vert");
	fShader = ShaderFactory::create("test/shader/basic.frag");
	program = ProgramBuilder::build(vShader, fShader);
	glUseProgram(program);
	
	// Calculate projection matrix
	mvpMatrixLocation = glGetUniformLocation(program, "MVPMatrix");
	if (mvpMatrixLocation < 0) {
		throw BasicException("Could not find transform location!");
	}
	orthoMatrix = Projection::orthographic(512, 512);
	orthoMatrix.toArray(orthoArray);
	glUniformMatrix4fv(mvpMatrixLocation, 1, false, orthoArray);
	
	// Make vertex buffer
	vbb.addAttribute("MCVertex", 2);
	vbb.setCapacity(3);
	vbo = vbb.toVertexBuffer();
	
	// Upload data to it
	vbo->bind();
	vbo->put(100, 400);
	vbo->put(100, 300);
	vbo->put(200, 400);
	vbo->flush();
	vbo->unbind();
	
	// Find MCVertex location
	mcVertexLocation = glGetAttribLocation(program, "MCVertex");
	if (mcVertexLocation < 0) {
		throw BasicException("Could not find MCVertex location!");
	}
	
}

void ProjectionTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(program);
	vbo->bind();
	
	glEnableVertexAttribArray(mcVertexLocation);
	glVertexAttribPointer(
			mcVertexLocation,                    // index
			2,                                   // size
			GL_FLOAT,                            // type
			false,                               // normalized
			vbo->getStride(),                    // stride
			(void*) vbo->getOffset("MCVertex")); // offset
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



#define HARNESS ProjectionTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testOrthographic)
RUN_TESTS
