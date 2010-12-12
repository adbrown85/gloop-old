/*
 * Glyph.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Glyph.hpp"


/** @brief Test fixture for Glyph. */
class GlyphTest : public Test {
public:
	void testToString();
	void testValidate();
};

/** Ensures glyph is converted to a string correctly. */
void GlyphTest::testToString() {
	
	GlyphMetrics metrics;
	Glyph *glyph;
	
	metrics.width = 5;
	metrics.height = 10;
	metrics.advance = 6;
	metrics.ascent = 4;
	metrics.descent = 3;
	
	glyph = new Glyph('c', metrics);
	
	assert(
			glyph->toString() == 
			string("Glyph") + 
			      " char='c' advance='6'" + 
			      " ascent='4' descent='3'" + 
			      " width='5' height='10'");
}

/** Ensures bad glyphs are rejected. */
void GlyphTest::testValidate() {
	
	GlyphMetrics metrics;
	Glyph *glyph;
	
	metrics.width = 0;
	metrics.height = 10;
	metrics.advance = 6;
	metrics.ascent = 7;
	metrics.descent = 3;
	
	try {
		glyph = new Glyph('c', metrics);
		assert(false);
	} catch (exception &e) {
	}
	
	metrics.width = 5;
	metrics.height = 0;
	metrics.advance = 6;
	metrics.ascent = 7;
	metrics.descent = 3;
	
	try {
		glyph = new Glyph('c', metrics);
		assert(false);
	} catch (exception &e) {
	}
	
	metrics.width = 5;
	metrics.height = 10;
	metrics.advance = 0;
	metrics.ascent = 7;
	metrics.descent = 3;
	
	try {
		glyph = new Glyph('c', metrics);
		assert(false);
	} catch (exception &e) {
	}
	
	metrics.width = 5;
	metrics.height = 10;
	metrics.advance = 6;
	metrics.ascent = 12;
	metrics.descent = 3;
	
	try {
		glyph = new Glyph('c', metrics);
		assert(false);
	} catch (exception &e) {
	}
}

/* Run the test. */
#define HARNESS GlyphTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testToString)
ADD_TEST(testValidate)
RUN_TESTS
