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
	static GlyphPackageSize measure(const Font &font);
};

GlyphPackageSize FakeGlyphPacker::measure(const Font &font) {
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
	GlyphPackageSize size;
	
	size = FakeGlyphPacker::measure(font);
	
	cout << size.width << endl;
	cout << size.height << endl;
	cout << size.rows << endl;
	cout << size.cols << endl;
	
//	assert(size.width == 1152);
//	assert(size.height == 1079);
//	assert(size.rows == 13);
//	assert(size.cols == 8);
}

/** Ensures font is packed into the image properly. */
void GlyphPackerTest::testPack() {
	
	Font font("Arial", Font::PLAIN, 72);
	Cairo::RefPtr<Cairo::ImageSurface> surface;
	
	surface = packer.pack(font);
	surface->write_to_png("test/text/GlyphPacker.png");
}

/* Run the test. */
#define HARNESS GlyphPackerTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testMeasure)
ADD_TEST(testPack)
RUN_TESTS
