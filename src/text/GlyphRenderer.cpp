/*
 * GlyphRenderer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphRenderer.hpp"

/** Initialize the glyph renderer. */
GlyphRenderer::GlyphRenderer() {
	
	vbo = makeVertexBuffer();
	program = makeShaderProgram();
	uMvpMatrixIndex = glGetUniformLocation(program, "MVPMatrix");
	aMcVertexIndex = glGetAttribLocation(program, "MCVertex");
	aTexCoord0Index = glGetAttribLocation(program, "TexCoord0");
}

/** Destroy the glyph renderer. */
GlyphRenderer::~GlyphRenderer() {
	if (vbo != NULL) {
		delete vbo;
	}
}

/** Initialize rendering with the glyph renderer.
 * 
 * @param width Width of the viewport
 * @param height Height of the viewport
 */
void GlyphRenderer::beginRendering(int width, int height) {
	
	glUseProgram(program);
	setMvpMatrix(width, height);
	
	vbo->bind();
	
	glEnableVertexAttribArray(aMcVertexIndex);
	glVertexAttribPointer(
			aMcVertexIndex,                         // index
			2,                                      // size
			GL_FLOAT,                               // type
			false,                                  // normalized
			vbo->getStride(),                       // stride
			(GLvoid*) vbo->getOffset("MCVertex"));  // offset
	
	glEnableVertexAttribArray(aTexCoord0Index);
	glVertexAttribPointer(
			aTexCoord0Index,                        // index
			2,                                      // size
			GL_FLOAT,                               // type
			false,                                  // normalized
			vbo->getStride(),                       // stride
			(GLvoid*) vbo->getOffset("TexCoord0")); // offset
}

/** Draw a glyph at a position.
 * 
 * @param glyph Visual representation of a character
 * @param x Position in X direction to render the glyph
 * @param y Position in Y direction to render the glyph
 * @param gc Coordinates of glyph in glyph texture 
 */
void GlyphRenderer::draw(Glyph *glyph, int x, int y, const GlyphCoords &gc) {
	
	int l, r, t, b;
	
	l = x;
	r = x + glyph->getWidth();
	t = y + glyph->getAscent();
	b = y - glyph->getDescent();
	
	vbo->rewind();
	vbo->put(l, t);  // 1
	vbo->put(gc.left, gc.top);
	vbo->put(l, b);  // 2
	vbo->put(gc.left, gc.bottom);
	vbo->put(r, t);  // 3
	vbo->put(gc.right, gc.top);
	vbo->put(l, b);  // 4
	vbo->put(gc.left, gc.bottom);
	vbo->put(r, b);  // 5
	vbo->put(gc.right, gc.bottom);
	vbo->put(r, t);  // 6
	vbo->put(gc.right, gc.top);
	vbo->flush();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

/** Finish rendering with the glyph renderer. */
void GlyphRenderer::endRendering() {
	
	glUseProgram(0);
	vbo->unbind();
}

//--------------------------------------------------------
// Helpers
//

/** @return VertexBuffer for a glyph renderer. */
VertexBuffer* GlyphRenderer::makeVertexBuffer() {
	
	VertexBufferBuilder vbb;
	
	vbb.addAttribute("MCVertex", 2);
	vbb.addAttribute("TexCoord0", 2);
	vbb.setCapacity(6);
	vbb.setUsage(GL_STREAM_DRAW);
	
	return vbb.toVertexBuffer();
}

/** @return Shader program for a glyph renderer. */
GLuint GlyphRenderer::makeShaderProgram() {
	
	GLuint vs, fs;
	
	vs = ShaderFactory::create("src/text/text.vert");
	fs = ShaderFactory::create("src/text/text.frag");
	
	return ProgramBuilder::build(vs, fs);
}

/** Change the modelview projection matrix in the program.
 * 
 * @param width Width of the viewport
 * @param height Height of the viewport
 */
void GlyphRenderer::setMvpMatrix(int width, int height) {
	
	float arr[16];
	Matrix mat;
	
	mat = Projection::orthographic(width, height);
	mat.toArray(arr);
	
	glUniformMatrix4fv(uMvpMatrixIndex, 1, false, arr);
}
