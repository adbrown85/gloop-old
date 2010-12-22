/*
 * GlyphTextureDrawTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphTexture.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferBuilder.hpp"
#include "ShaderFactory.hpp"
#include "ProgramBuilder.hpp"
#include "GlyphTexture.hpp"
#include "GlyphFactory.hpp"


/** Test fixture for GlyphTexture. */
class GlyphTextureDrawTest : public Test {
public:
	GlyphTextureDrawTest();
	virtual void testDraw();
	virtual void onCanvasInitEvent(Canvas &canvas);
	virtual void onCanvasDisplayEvent(Canvas &canvas);
private:
	VertexBuffer *vbo;
	GLuint program;
	GLint pointLoc, coordLoc;
	Font *font;
	GlyphFactory *glyphFactory;
	GlyphTexture *glyphTexture;
};

/** Initialize the test fixture. */
GlyphTextureDrawTest::GlyphTextureDrawTest() {
	vbo = NULL;
	program = 0;
	pointLoc = -1;
	coordLoc = -1;
	glyphFactory = NULL;
	glyphTexture = NULL;
	font = new Font("Arial", Font::PLAIN, 72);
}

/** Start the test. */
void GlyphTextureDrawTest::testDraw() {
	runWindow();
}

/** Initialize OpenGL items. */
void GlyphTextureDrawTest::onCanvasInitEvent(Canvas &canvas) {
	
	GLuint vShader, fShader;
	VertexBufferBuilder vbb;
	Glyph *glyph;
	GlyphCoords gc;
	
	glyphFactory = GlyphFactory::getInstance(*font);
	glyphTexture = GlyphTexture::getInstance(*font);
	glyph = glyphFactory->create('@');
	gc = glyphTexture->find(glyph);
	
	vbb.addAttribute("MCVertex", 2);
	vbb.addAttribute("TexCoord0", 2);
	vbb.setCapacity(6);
	vbo = vbb.toVertexBuffer();
	
	vbo->bind();
	vbo->put(+0.5, +0.5); // 1
	vbo->put(gc.right, gc.top);
	vbo->put(-0.5, +0.5); // 2
	vbo->put(gc.left, gc.top);
	vbo->put(-0.5, -0.5); // 3
	vbo->put(gc.left, gc.bottom);
	vbo->put(+0.5, +0.5); // 4
	vbo->put(gc.right, gc.top);
	vbo->put(-0.5, -0.5); // 5
	vbo->put(gc.left, gc.bottom);
	vbo->put(+0.5, -0.5); // 6
	vbo->put(gc.right, gc.bottom);
	vbo->flush();
	vbo->unbind();
	
	vShader = ShaderFactory::create("test/text/texture.vert");
	fShader = ShaderFactory::create("test/text/texture.frag");
	program = ProgramBuilder::build(vShader, fShader);
	
	pointLoc = glGetAttribLocation(program, "MCVertex");
	if (pointLoc < 0) {
		throw BasicException("Location of MCVertex not found!");
	}
	
	coordLoc = glGetAttribLocation(program, "TexCoord0");
	if (coordLoc < 0) {
		throw BasicException("Location of TexCoord0 not found!");
	}
}

/** Draw everything. */
void GlyphTextureDrawTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0, 1, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(program);
	vbo->bind();
	
	glEnableVertexAttribArray(pointLoc);
	glVertexAttribPointer(
			pointLoc,                               // index
			2,                                      // size
			GL_FLOAT,                               // type
			false,                                  // normalized
			vbo->getStride(),                       // stride
			(GLvoid*) vbo->getOffset("MCVertex"));  // offset
	
	glEnableVertexAttribArray(coordLoc);
	glVertexAttribPointer(
			coordLoc,                               // index
			2,                                      // size
			GL_FLOAT,                               // type
			false,                                  // normalized
			vbo->getStride(),                       // stride
			(GLvoid*) vbo->getOffset("TexCoord0")); // offset
	
	glyphTexture->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}



/* Run the test. */
#define HARNESS GlyphTextureDrawTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDraw)
RUN_TESTS
