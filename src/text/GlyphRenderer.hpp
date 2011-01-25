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


/** @brief Draw glyphs to the screen. */
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
