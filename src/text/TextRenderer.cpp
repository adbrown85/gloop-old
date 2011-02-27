/*
 * TextRenderer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TextRenderer.hpp"

/** Creates a text renderer from a font.
 * 
 * @param font Style of text
 */
TextRenderer::TextRenderer(const Font &font) {
	glyphFactory = GlyphFactory::getInstance(font);
	glyphTexture = GlyphTexture::getInstance(font);
	glyphRenderer = new GlyphRenderer();
}

/** Destroys the text renderer. */
TextRenderer::~TextRenderer() {
	if (glyphRenderer != NULL) {
		delete glyphRenderer;
	}
}

/** Starts a render cycle with the text renderer.
 * 
 * @param width Size of viewport in X direction
 * @param height Size of viewport in Y direction
 */
void TextRenderer::begin(int width, int height) {
	glyphTexture->bind();
	glyphRenderer->beginRendering(width, height);
}

/** Draws text at a position on the screen.
 * 
 * @param text Characters to draw
 * @param x Position to draw characters on X axis
 * @param y Position to draw characters on Y axis
 */
void TextRenderer::draw(const string &text, int x, int y) {
	
	Glyph *glyph;
	GlyphCoords gc;
	
	for (int i=0; i<text.length(); ++i) {
		glyph = glyphFactory->create(text[i]);
		gc = glyphTexture->find(glyph);
		glyphRenderer->draw(glyph, x, y, gc);
		x += glyph->getAdvance();
	}
}

/** Finishes a render cycle with the text renderer. */
void TextRenderer::end() {
	glyphRenderer->endRendering();
}
