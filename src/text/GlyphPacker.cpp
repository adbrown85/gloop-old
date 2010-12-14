/*
 * GlyphPacker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphPacker.hpp"

/** Creates a glyph packer. */
GlyphPacker::GlyphPacker(const Font &font) : font(font) {
	
	factory = GlyphFactory::getInstance(font);
}

/** Packs glyphs into an image. */
void GlyphPacker::pack() {
	
	measure();
	prepare();
	fill();
	
	package.image = surface;
}

/** @return Package that was built. */
GlyphPackage GlyphPacker::getPackage() {
	return package;
}

//--------------------------------------------------------
// Helpers
//

/** Make package appropriate size. */
void GlyphPacker::measure() {
	
    package.metrics.width = findMaxWidth();
    package.metrics.height = factory->getFontHeight();
    package.metrics.descent = factory->getFontDescent();
    package.rows = 1;
    package.cols = 1;
    package.width = package.metrics.width;
    package.height = package.metrics.height;
    
    for (int tally=1; tally<GLYPH_PACKER_GLYPHS_COUNT; ) {
       if (package.width < package.height) {
          package.width += package.metrics.width;
          tally += package.rows;
          ++(package.cols);
       } else {
          package.height += package.metrics.height;
          tally += package.cols;
          ++(package.rows);
       }
    }
}

/** Set up the measured package to be drawn into. */
void GlyphPacker::prepare() {
	
	// Make image and context
	surface = Cairo::ImageSurface::create(
			Cairo::FORMAT_A8,
			package.width, package.height);
	context = Cairo::Context::create(surface);
	
	// Set context to use font
	context->select_font_face(
			font.getFamily(),
			font.toCairoFontSlant(),
			font.toCairoFontWeight());
	context->set_font_size(font.getSize());
}

/** Draw glyphs into the prepared package. */
void GlyphPacker::fill() {
	
	int x, y;
	char character = '!';
	
	x = 0;
	y = package.metrics.height - package.metrics.descent;
	for (int i=0; i<package.rows; ++i) {
		for (int j=0; j<package.cols && character<127; ++j) {
			store(character, x, y);
			x += package.metrics.width;
			++character;
		}
		x = 0;
		y += package.metrics.height;
	}
}

/** Store glyph in package. */
void GlyphPacker::store(char c, int x, int y) {
	
	GlyphLocation location;
	Glyph *glyph = factory->create(c);
	char arr[2] = { c, '\0' };
	
	context->move_to(x, y);
	context->show_text(arr);
	
	location.left   = x;
	location.right  = x + glyph->getWidth();
	location.top    = y - glyph->getAscent();
	location.bottom = y + glyph->getDescent();
	
	package.locations[c] = location;
}

/** @return Maximum width of glyphs in font. */
int GlyphPacker::findMaxWidth() {
	
	Glyph *glyph;
	int max = 0;
	
	for (char c='!'; c<='~'; ++c) {
		glyph = factory->create(c);
		if (glyph->getWidth() > max) {
			max = glyph->getWidth();
		}
	}
	return max;
}
