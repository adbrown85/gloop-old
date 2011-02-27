/*
 * GlyphRenderer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphRenderer.hpp"

/** Initializes the glyph renderer. */
GlyphRenderer::GlyphRenderer() {
	
	vbo = makeVertexBuffer();
	program = makeShaderProgram();
	uMvpMatrixIndex = glGetUniformLocation(program, "MVPMatrix");
	aMcVertexIndex = glGetAttribLocation(program, "MCVertex");
	aTexCoord0Index = glGetAttribLocation(program, "TexCoord0");
	count = 0;
}

/** Destroys the glyph renderer. */
GlyphRenderer::~GlyphRenderer() {
	if (vbo != NULL) {
		delete vbo;
	}
}

/** Initializes rendering with the glyph renderer.
 * 
 * @param width Width of the viewport
 * @param height Height of the viewport
 */
void GlyphRenderer::beginRendering(int width, int height) {
	
	glUseProgram(program);
	setMvpMatrix(width, height);
	
	vbo->bind();
	vbo->rewind();
	
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

/** Draws a glyph at a position.
 * 
 * @param glyph Visual representation of a character
 * @param x Position in X direction to render the glyph
 * @param y Position in Y direction to render the glyph
 * @param gc Coordinates of glyph in glyph texture 
 */
void GlyphRenderer::draw(Glyph *glyph, int x, int y, const GlyphCoords &gc) {
	
	int l = x;                                   // Left screen coordinate
	int r = x + glyph->getWidth();               // Right screen coordinate
	int t = y + glyph->getAscent();              // Top screen coordinate
	int b = y - glyph->getDescent();             // Bottom screen coordinate
	
	// Left triangle
	vbo->put(l, t);
	vbo->put(gc.left, gc.top);
	vbo->put(l, b);
	vbo->put(gc.left, gc.bottom);
	vbo->put(r, t);
	vbo->put(gc.right, gc.top);
	
	// Right triangle
	vbo->put(l, b);
	vbo->put(gc.left, gc.bottom);
	vbo->put(r, b);
	vbo->put(gc.right, gc.bottom);
	vbo->put(r, t);
	vbo->put(gc.right, gc.top);
	
	// Check if need to flush
	if (++count >= GLYPH_CAPACITY) {
		flush();
	}
}

/** Finishes rendering with the glyph renderer. */
void GlyphRenderer::endRendering() {
	
	flush();
	
	glUseProgram(0);
	vbo->unbind();
}

/** Forces all queued glyphs to be rendered. */
void GlyphRenderer::flush() {
	
	// Do nothing if no glyphs queued
	if (count == 0) {
		return;
	}
	
	// Push vertices to VBO and draw
	vbo->flush();
	glDrawArrays(GL_TRIANGLES, 0, count * VERTICES_PER_GLYPH);
	
	// Reset the VBO and glyph count
	vbo->rewind();
	count = 0;
}

//--------------------------------------------------------
// Helpers
//

/** Returns vertex buffer object for a glyph renderer. */
VertexBuffer* GlyphRenderer::makeVertexBuffer() {
	
	VertexBufferBuilder vbb;
	
	vbb.addAttribute("MCVertex", 2);
	vbb.addAttribute("TexCoord0", 2);
	vbb.setCapacity(VERTEX_CAPACITY);
	vbb.setUsage(GL_STREAM_DRAW);
	
	return vbb.toVertexBuffer();
}

/** Returns shader program for a glyph renderer. */
GLuint GlyphRenderer::makeShaderProgram() {
	
	GLuint vs, fs;
	
	vs = ShaderFactory::create("src/text/text.vert");
	fs = ShaderFactory::create("src/text/text.frag");
	
	return ProgramBuilder::build(vs, fs);
}

/** Changes the modelview projection matrix in the program.
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
