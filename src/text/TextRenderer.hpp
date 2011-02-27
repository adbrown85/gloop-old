/*
 * TextRenderer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP
#include "gloop_common.h"
#include "GlyphRenderer.hpp"
#include "GlyphFactory.hpp"
#include "GlyphTexture.hpp"
using namespace std;


/** Utility for rendering text. */
class TextRenderer {
public:
	TextRenderer(const Font &font);
	virtual ~TextRenderer();
	virtual void begin(int width, int height);
	virtual void draw(const string &text, int x, int y);
	virtual void end();
private:
	GlyphFactory *glyphFactory;
	GlyphRenderer *glyphRenderer;
	GlyphTexture *glyphTexture;
};

#endif
