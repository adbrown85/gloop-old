/*
 * GlyphPacker.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphPacker.hpp"

class FakeGlyphPacker : public GlyphPacker {
public:
	static GlyphPackage measure(const Font &font);
};

GlyphPackage FakeGlyphPacker::measure(const Font &font) {
	return GlyphPacker::measure(font);
}


/** Test fixture for GlyphPacker. */
class GlyphPackerTest : public Test {
public:
	void testMeasure();
	void testPack();
private:
	FakeGlyphPacker packer;
};

/** Ensures font is measured properly. */
void GlyphPackerTest::testMeasure() {
	
	Font font("Arial", Font::PLAIN, 72);
	GlyphPackage gp  = FakeGlyphPacker::measure(font);
	
//	cout << gp.width << endl;
//	cout << gp.height << endl;
//	cout << gp.rows << endl;
//	cout << gp.cols << endl;
	
	assert(gp.width == 748);
	assert(gp.height == 747);
	assert(gp.rows == 9);
	assert(gp.cols == 11);
}

/** Ensures font is packed into the image properly. */
void GlyphPackerTest::testPack() {
	
	Font font("Arial", Font::PLAIN, 72);
	GlyphPackage gp = packer.pack(font);
	
	gp.image->write_to_png("test/text/GlyphPacker.png");
}

/* Run the test. */
#define HARNESS GlyphPackerTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testMeasure)
ADD_TEST(testPack)
RUN_TESTS
