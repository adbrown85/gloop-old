/*
 * GlyphPacker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphPacker.hpp"

GlyphPacker::GlyphPacker() {
	// TODO Auto-generated method stub
}

Cairo::RefPtr<Cairo::ImageSurface> GlyphPacker::pack(const Font &font) {
	
	Cairo::RefPtr<Cairo::ImageSurface> surface;
	Cairo::RefPtr<Cairo::Context> context;
	GlyphPackageSize size = measure(font);
	int x, y;
	char character = '!';
	char arr[2] = { '\0', '\0' };
	
	// Make surface and context
	surface = Cairo::ImageSurface::create(
			Cairo::FORMAT_A8,
			size.width, size.height);
	context = Cairo::Context::create(surface);
	
	// Set context to use font
	context->select_font_face(
			font.getFamily(),
			font.toCairoFontSlant(),
			font.toCairoFontWeight());
	context->set_font_size(font.getSize());
	
	x = 0;
	y = size.glyphHeight - size.glyphDescent;
	for (int i=0; i<size.rows; ++i) {
		for (int j=0; j<size.cols && character<127; ++j) {
			arr[0] = character;
			context->move_to(x, y);
			context->show_text(arr);
			x += size.glyphWidth;
			++character;
		}
		x = 0;
		y += size.glyphHeight;
	}
	
	return surface;
}

//--------------------------------------------------------
// Helpers
//

/** @return Size of image needed to hold font. */
GlyphPackageSize GlyphPacker::measure(const Font &font) {
	
	GlyphPackageSize size;
	GlyphFactory *gf = GlyphFactory::getInstance(font);
    
    size.rows = 1;
    size.cols = 1;
    size.glyphWidth = findMaxWidth(font);
    size.glyphHeight = gf->getFontHeight();
    size.glyphDescent = gf->getFontDescent();
    size.width = size.glyphWidth;
    size.height = size.glyphHeight;
    
    for (int tally=1; tally<GLYPH_PACKER_GLYPHS_COUNT; ) {
       if (size.width < size.height) {
          size.width += size.glyphWidth;
          tally += size.rows;
          size.cols++;
       } else {
          size.height += size.glyphHeight;
          tally += size.cols;
          size.rows++;
       }
    }
	
	return size;
}

int GlyphPacker::findMaxWidth(const Font &font) {
	
	GlyphFactory *gf = GlyphFactory::getInstance(font);
	Glyph *glyph;
	int max = 0;
	
	for (char c='!'; c<='~'; ++c) {
		glyph = gf->create(c);
		if (glyph->getWidth() > max)
			max = glyph->getWidth();
	}
	return max;
}
