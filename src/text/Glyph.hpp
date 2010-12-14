/*
 * Glyph.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLYPH_HPP
#define GLYPH_HPP
#include "gloop_common.h"
#include <edo/BasicException.hpp>
using namespace std;


/* Measurements of a glyph. */
struct GlyphMetrics {
	int advance;
	int ascent, descent;
	int width, height;
};

/** @brief Visual depiction of a character. */
class Glyph {
public:
	Glyph(char character, const GlyphMetrics &metrics);
	virtual ~Glyph() { }
// Getters and setters
	virtual int getAdvance() const;
	virtual int getAscent() const;
	virtual int getDescent() const;
	virtual int getWidth() const;
	virtual int getHeight() const;
// Converters
	virtual char toChar() const;
	virtual string toString() const;
private:
	char character;
	GlyphMetrics metrics;
// Helpers
	void validate();
};

/** @return Distance from the start of this glyph to the start of the next. */
inline int Glyph::getAdvance() const {return metrics.advance;}

/** @return Distance from baseline to top of glyph. */
inline int Glyph::getAscent() const {return metrics.ascent;}

/** @return Distance glyph extends below the baseline. */
inline int Glyph::getDescent() const {return metrics.descent;}

/** @return Width of the glyph. */
inline int Glyph::getWidth() const {return metrics.width;}

/** @return Height of the glyph. */
inline int Glyph::getHeight() const {return metrics.height;}

/** @return Character this glyph represents. */
inline char Glyph::toChar() const {return character;}

#endif
