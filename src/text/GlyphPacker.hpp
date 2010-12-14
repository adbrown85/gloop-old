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

/* Position and size of a glyph in the image. */
struct GlyphLocation {
	int x, y;
	int width, height;
};

/* Image with glyphs in it. */
struct GlyphPackage {
	Cairo::RefPtr<Cairo::ImageSurface> image;
	int width, height;
	int rows, cols;
	GlyphMetrics metrics;
	map<char,GlyphLocation> locations;
};

/** @brief Delegate responsible for putting glyphs in an image. */
class GlyphPacker {
public:
	GlyphPacker(const Font &font);
	virtual ~GlyphPacker() { }
	virtual void pack();
	virtual GlyphPackage getPackage();
private:
	Font font;
	GlyphPackage package;
	GlyphFactory *factory;
	Cairo::RefPtr<Cairo::Context> context;
	Cairo::RefPtr<Cairo::ImageSurface> surface;
// Helpers
	void measure();
	void prepare();
	void fill();
	void store(char c, int x, int y);
	int findMaxWidth();
};

#endif
