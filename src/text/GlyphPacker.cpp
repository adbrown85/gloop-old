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

GlyphPackage GlyphPacker::pack(const Font &font) {
	
	Cairo::RefPtr<Cairo::Context> context;
	GlyphPackage gp = measure(font);
	int x, y;
	char character = '!';
	char arr[2] = { '\0', '\0' };
	
	// Make image and context
	gp.image = Cairo::ImageSurface::create(
			Cairo::FORMAT_A8,
			gp.width, gp.height);
	context = Cairo::Context::create(gp.image);
	
	// Set context to use font
	context->select_font_face(
			font.getFamily(),
			font.toCairoFontSlant(),
			font.toCairoFontWeight());
	context->set_font_size(font.getSize());
	
	// Draw into image
	x = 0;
	y = gp.metrics.height - gp.metrics.descent;
	for (int i=0; i<gp.rows; ++i) {
		for (int j=0; j<gp.cols && character<127; ++j) {
			arr[0] = character;
			context->move_to(x, y);
			context->show_text(arr);
			x += gp.metrics.width;
			++character;
		}
		x = 0;
		y += gp.metrics.height;
	}
	
	return gp;
}

//--------------------------------------------------------
// Helpers
//

/** @return Package with size information. */
GlyphPackage GlyphPacker::measure(const Font &font) {
	
	GlyphPackage gp;
	GlyphFactory *gf = GlyphFactory::getInstance(font);
    
    gp.metrics.width = findMaxWidth(font);
    gp.metrics.height = gf->getFontHeight();
    gp.metrics.descent = gf->getFontDescent();
    gp.rows = 1;
    gp.cols = 1;
    gp.width = gp.metrics.width;
    gp.height = gp.metrics.height;
    
    for (int tally=1; tally<GLYPH_PACKER_GLYPHS_COUNT; ) {
       if (gp.width < gp.height) {
          gp.width += gp.metrics.width;
          tally += gp.rows;
          gp.cols++;
       } else {
          gp.height += gp.metrics.height;
          tally += gp.cols;
          gp.rows++;
       }
    }
    
	return gp;
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
