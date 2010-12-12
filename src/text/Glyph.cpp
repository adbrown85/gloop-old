/*
 * Glyph.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Glyph.hpp"

/** Create a glyph from a character and measurements. */
Glyph::Glyph(char character, const GlyphMetrics &metrics) {
	
	this->character = character;
	this->metrics = metrics;
	
	validate();
}

//--------------------------------------------------------
// Helpers
//

/** Makes sure fields are valid. */
void Glyph::validate() {
	
	if (!isprint(character)) {
		BasicException e;
		e << "[Glyph] Character must be printable!";
		throw e;
	}
	
	if ((metrics.advance <= 0)
			|| (metrics.height <= 0)
			|| (metrics.width <= 0)) {
		BasicException e;
		e << "[Glyph] Invalid measurements!";
		throw e;
	}
	
	if ((metrics.ascent > metrics.height)
			|| (metrics.descent > metrics.height)) {
		BasicException e;
		e << "[Glyph] Ascent and descent must be less than height!";
		throw e;
	}
}

//--------------------------------------------------------
// Converters
//

/** @return String representation of this object. */
string Glyph::toString() const {
	
	ostringstream ss;
	
	ss << "Glyph";
	ss << " char='" << character << "'";
	ss << " advance='" << metrics.advance << "'";
	ss << " ascent='" << metrics.ascent << "'";
	ss << " descent='" << metrics.descent << "'";
	ss << " width='" << metrics.width << "'";
	ss << " height='" << metrics.height << "'";
	return ss.str();
}

