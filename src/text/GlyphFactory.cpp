/*
 * GlyphFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlyphFactory.hpp"
map<Font,GlyphFactory*> GlyphFactory::instances;

/** Create a glyph factory using a font. */
GlyphFactory::GlyphFactory(const Font &font) : font(font) {
	
	initScaledFont(this->font);
	initFontExtents(this->scaledFont);
}

/** Copy constructor. */
GlyphFactory::GlyphFactory(const GlyphFactory &gf) : font(gf.font) {
	throw BasicException("[GlyphFactory] Should not be copied!");
}

/** @return Instance that can make glyphs for font. */
GlyphFactory* GlyphFactory::getInstance(Font font) {
	
	map<Font,GlyphFactory*>::iterator it;
	GlyphFactory *gf;
	
	// Check if already made
	it = instances.find(font);
	if (it != instances.end()) {
		return it->second;
	}
	
	// Otherwise make it
	gf = new GlyphFactory(font);
	instances[font] = gf;
	return gf;
}

/** @return Glyph representing character. */
Glyph* GlyphFactory::create(char character) {
	
	Glyph *glyph;
	map<char,Glyph*>::iterator it;
	
	// Check if already made
	it = inventory.find(character);
	if (it != inventory.end()) {
		return it->second;
	}
	
	// Otherwise make it
	glyph = makeGlyph(character);
	inventory[character] = glyph;
	return glyph;
}

//--------------------------------------------------------
// Helpers
//

void GlyphFactory::initScaledFont(const Font &font) {
	
	Cairo::RefPtr<Cairo::ImageSurface> surface;
	Cairo::RefPtr<Cairo::Context> context;
	
	// Create an in-memory surface
	surface = Cairo::ImageSurface::create(Cairo::FORMAT_A1, 1, 1);
	context = Cairo::Context::create(surface);
	
	// Get the scaled font from it
	context->select_font_face(
			font.getFamily(),
			toFontSlant(font.getStyle()),
			toFontWeight(font.getStyle()));
	context->set_font_size(font.getSize());
	scaledFont = context->get_scaled_font();
}

void GlyphFactory::initFontExtents(Cairo::RefPtr<Cairo::ScaledFont> sf) {
	
	sf->extents(fontExtents);
}

Cairo::FontSlant GlyphFactory::toFontSlant(Font::Style style) {
	
	switch (style) {
	case Font::ITALIC:
		return Cairo::FONT_SLANT_ITALIC;
	default:
		return Cairo::FONT_SLANT_NORMAL;
	}
}

Cairo::FontWeight GlyphFactory::toFontWeight(Font::Style style) {
	
	switch (style) {
	case Font::BOLD:
		return Cairo::FONT_WEIGHT_BOLD;
	default:
		return Cairo::FONT_WEIGHT_NORMAL;
	}
}

Glyph* GlyphFactory::makeGlyph(char character) {
	
	Cairo::TextExtents textExtents;
	GlyphMetrics metrics;
	char str[2];
	
	str[0] = character;
	str[1] = '\0';
	
	scaledFont->text_extents(str, textExtents);
	
	metrics.width = textExtents.width;
	metrics.height = fontExtents.height;
	metrics.advance = textExtents.x_advance;
	metrics.ascent = fontExtents.ascent;
	metrics.descent = fontExtents.descent;
	
	return new Glyph(character, metrics);
}

