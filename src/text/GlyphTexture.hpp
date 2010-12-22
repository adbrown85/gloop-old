/*
 * GlyphTexture.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYPHTEXTURE_HPP
#define GLYPHTEXTURE_HPP
#include "gloop_common.h"
#include <cairomm/cairomm.h>
#include <edo/BasicException.hpp>
#include "Font.hpp"
#include "Glyph.hpp"
#include "GlyphPacker.hpp"
using namespace std;


/* Position of a glyph in a texture. */
struct GlyphCoords {
	float left, right;
	float top, bottom;
};

/** @brief Texture storing multiple glyphs. */
class GlyphTexture {
public:
	static GlyphTexture* getInstance(const Font &font);
	virtual ~GlyphTexture() { }
	virtual GlyphCoords find(Glyph *glyph);
	virtual void bind();
	virtual void unbind();
private:
	Font font;
	GLuint handle;
	map<char,GlyphCoords> coords;
	GlyphPackage package;
// Helpers
	void storeCoords();
	void storeCoords(char c, GlyphLocation &gl);
	static GlyphPackage makePackage(const Font &font);
	void upload();
// Instance control
	static map<Font,GlyphTexture*> instances;
	GlyphTexture(const Font &font);
	GlyphTexture(const GlyphTexture &gt);
};

#endif
