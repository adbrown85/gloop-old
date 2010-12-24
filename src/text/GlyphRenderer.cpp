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
}

/** Destroy the glyph renderer. */
GlyphRenderer::~GlyphRenderer() {
	if (vbo != NULL) {
		delete vbo;
	}
}

void GlyphRenderer::beginRendering(int width, int height) {
	
	glUseProgram(program);
	setMvpMatrix(width, height);
	
	vbo->bind();
	
	glEnableVertexAttribArray(aMcVertexIndex);
	glVertexAttribPointer(
			aMcVertexIndex,                        // index
			2,                                     // size
			GL_FLOAT,                              // type
			false,                                 // normalized
			vbo->getStride(),                      // stride
			(GLvoid*) vbo->getOffset("MCVertex")); // offset
}

void GlyphRenderer::draw(Glyph *glyph, int x, int y, const GlyphCoords &gc) {
	
	int l, r, t, b;
	
	l = x;
	r = x + glyph->getWidth();
	t = y + glyph->getAscent();
	b = y - glyph->getDescent();
	
	vbo->rewind();
	vbo->put(l, t);
	vbo->put(l, b);
	vbo->put(r, t);
	vbo->put(l, b);
	vbo->put(r, b);
	vbo->put(r, t);
	vbo->flush();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

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
//	vbb.addAttribute("MCVertex", 2);
//	vbb.addAttribute("TexCoord0");
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

void GlyphRenderer::setMvpMatrix(int width, int height) {
	
	float arr[16];
	Matrix mat;
	
	mat = Projection::orthographic(width, height);
	mat.toArray(arr);
	
	glUniformMatrix4fv(uMvpMatrixIndex, 1, false, arr);
}
