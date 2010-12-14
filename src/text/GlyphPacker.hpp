/*
 * GlyphPacker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYPHPACKER_HPP
#define GLYPHPACKER_HPP
#include "gloop_common.h"
#include <cairomm/refptr.h>
#include <cairomm/surface.h>
#include "GlyphFactory.hpp"
#define GLYPH_PACKER_GLYPHS_COUNT 96
using namespace std;

/* Measure of width and height. */
struct GlyphPackageSize {
	int width, height;
	int rows, cols;
	int glyphWidth, glyphHeight;
	int glyphDescent;
};

/** @brief Delegate responsible for putting glyphs in an image. */
class GlyphPacker {
public:
	GlyphPacker();
	virtual ~GlyphPacker() { }
	virtual Cairo::RefPtr<Cairo::ImageSurface> pack(const Font &font);
protected:
	static GlyphPackageSize measure(const Font &font);
	static int findMaxWidth(const Font &font);
	static Cairo::FontSlant toFontSlant(Font::Style style);
	static Cairo::FontWeight toFontWeight(Font::Style style);
};

#endif
