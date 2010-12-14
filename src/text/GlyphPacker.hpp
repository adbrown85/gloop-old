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

/* Image with glyphs in it. */
struct GlyphPackage {
	Cairo::RefPtr<Cairo::ImageSurface> image;
	int width, height;
	int rows, cols;
	GlyphMetrics metrics;
};

/** @brief Delegate responsible for putting glyphs in an image. */
class GlyphPacker {
public:
	GlyphPacker();
	virtual ~GlyphPacker() { }
	virtual GlyphPackage pack(const Font &font);
protected:
	static GlyphPackage measure(const Font &font);
	static int findMaxWidth(const Font &font);
};

#endif
