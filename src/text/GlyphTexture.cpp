/*
 * GlyphTexture.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphTexture.hpp"
map<Font,GlyphTexture*> GlyphTexture::instances;

/** Create a glyph texture from a font. */
GlyphTexture::GlyphTexture(const Font &font) : font(font) {
	
	package = makePackage(font);
	storeCoords();
	upload();
}

/** @throw BasicException if code tries to copy a GlyphTexture. */
GlyphTexture::GlyphTexture(const GlyphTexture &gt) : font(font) {
	throw BasicException("[GlyphTexture] Unsupported copy!");
}

/** @return GlyphTexture instance containing font's glyphs. */
GlyphTexture* GlyphTexture::getInstance(const Font &font) {
	
	map<Font,GlyphTexture*>::iterator it;
	GlyphTexture *gt;
	
	// Check if already made
	it = instances.find(font);
	if (it != instances.end()) {
		return it->second;
	}
	
	// Make it
	gt = new GlyphTexture(font);
	instances[font] = gt;
	return gt;
}

/** Enables the texture. */
void GlyphTexture::bind() {
	glBindTexture(GL_TEXTURE_2D, handle);
}

/** Disables the texture. */
void GlyphTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

/** @return Coordinates of glyph in the texture. */
GlyphCoords GlyphTexture::find(Glyph *glyph) {
	
	map<char,GlyphCoords>::iterator it;
	
	it = coords.find(glyph->toChar());
	if (it == coords.end()) {
		BasicException e;
		e << "[GlyphTexture] Could not find	'" << glyph->toChar() << "'!";
		throw e;
	}
	
	return it->second;
}

//--------------------------------------------------------
// Helpers
//

/** Store coordinates of all glyphs in package. */
void GlyphTexture::storeCoords() {
	
	map<char,GlyphLocation>::iterator it;
	
	for (it=package.locations.begin(); it!=package.locations.end(); ++it) {
		storeCoords(it->first, it->second);
	}
}

/** Store coordinates of a single glyph. */
void GlyphTexture::storeCoords(char c, GlyphLocation &gl) {
	
	GlyphCoords gc;
	
	gc.left   = ((float) gl.left) / package.width;
	gc.right  = ((float) gl.right) / package.width;
	gc.top    = ((float) gl.top) / package.height;
	gc.bottom = ((float) gl.bottom) / package.height;
	
	coords[c] = gc;
}

/** @return Glyph package containing glyphs for font. */
GlyphPackage GlyphTexture::makePackage(const Font &font) {
	
	GlyphPacker packer(font);
	
	packer.pack();
	return packer.getPackage();
}

/** Allocate and fill the texture. */
void GlyphTexture::upload() {
	
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(
			GL_TEXTURE_2D,                        // target
			0,                                    // level
			GL_LUMINANCE,                         // internal format
			(GLsizei) package.width,              // width
			(GLsizei) package.height,             // height
			0,                                    // border
			GL_LUMINANCE,                         // format
			GL_UNSIGNED_BYTE,                     // type
			(GLvoid*) package.image->get_data()); // pixels
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
