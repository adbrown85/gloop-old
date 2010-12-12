/*
 * GlyphFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYPHFACTORY_HPP
#define GLYPHFACTORY_HPP
#include "gloop_common.h"
#include <cairomm/cairomm.h>
#include "Font.hpp"
#include "Glyph.hpp"
using namespace std;


/** @brief Common source of Glyph objects. */
class GlyphFactory {
public:
	static GlyphFactory* getInstance(Font font);
	virtual ~GlyphFactory() { }
	Glyph* create(char c);
private:
	map<char,Glyph*> inventory;
	Font font;
	Cairo::RefPtr<Cairo::ScaledFont> scaledFont;
	Cairo::FontExtents fontExtents;
// Helpers
	Glyph* makeGlyph(char character);
	void initScaledFont(const Font &font);
	void initFontExtents(Cairo::RefPtr<Cairo::ScaledFont> sf);
	static Cairo::FontSlant toFontSlant(Font::Style style);
	static Cairo::FontWeight toFontWeight(Font::Style style);
// Instance control
	static map<Font,GlyphFactory*> instances;
	GlyphFactory(const Font &font);
	GlyphFactory(const GlyphFactory &gf);
};

#endif
