/*
 * GlyphRenderer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_GLYPHRENDERER_HPP
#define GLOOP_GLYPHRENDERER_HPP
#include "gloop_common.h"
#include "Font.hpp"
#include "Glyph.hpp"
#include "GlyphTexture.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferBuilder.hpp"
#include "Projection.hpp"
#include "ShaderFactory.hpp"
#include "ProgramBuilder.hpp"


/** @brief Component for drawing glyphs.
 * 
 * To use a glyph renderer, first create one.  Then call
 * beginRendering() and start drawing glyphs using draw().  When all
 * the glyphs have been drawn, call endRendering().
 * 
 * To increase performance, <i>GlyphRenderer</i> buffers the glyphs
 * that are drawn with it.  For that reason nothing is actually
 * rendered until endRendering() or flush() is called.
 * 
 * Because quads are no longer supported directly by OpenGL, this
 * implementation represents glyphs as two triangles.  Therefore each
 * glyph has six vertices.  It then follows that when we do flush
 * that we must pass the number of queued glyphs multiplied by six to
 * OpenGL.
 */
class GlyphRenderer {
public:
	GlyphRenderer();
	virtual ~GlyphRenderer();
	virtual void beginRendering(int width, int height);
	virtual void draw(Glyph *glyph, int x, int y, const GlyphCoords &gc);
	virtual void endRendering();
private:
	VertexBuffer *vbo;
	GLuint program;
	GLint uMvpMatrixIndex;
	GLint aMcVertexIndex, aTexCoord0Index;
// Helpers
	static VertexBuffer* makeVertexBuffer();
	static GLuint makeShaderProgram();
	void setMvpMatrix(int width, int height);
};

#endif
