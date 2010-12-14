/*
 * GlyphPacker.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphPacker.hpp"


/** Test fixture for GlyphPacker. */
class GlyphPackerTest : public Test {
public:
	virtual void setUp();
	virtual void tearDown();
	void testMeasure();
	void testPack();
	void testLocations();
private:
	Font *font;
	GlyphPacker *packer;
	GlyphPackage package;
};

void GlyphPackerTest::setUp() {
	
	font = new Font("Arial", Font::PLAIN, 72);
	packer = new GlyphPacker(*font);
	packer->pack();
	package = packer->getPackage();
}

void GlyphPackerTest::tearDown() {
	
	delete font;
	delete packer;
}

/** Ensures font is measured properly. */
void GlyphPackerTest::testMeasure() {
	
	assert(package.width == 748);
	assert(package.height == 747);
	assert(package.rows == 9);
	assert(package.cols == 11);
}

/** Ensures font is packed into the image properly. */
void GlyphPackerTest::testPack() {
	
	package.image->write_to_png("test/text/GlyphPacker.png");
}

void GlyphPackerTest::testLocations() {
	
	map<char,GlyphLocation>::iterator it;
	
	it = package.locations.find('A');
	if (it == package.locations.end()) {
		throw BasicException("Could not find location!");
	}
	
	assert(it->second.x == 680);
	assert(it->second.y == 233);
	assert(it->second.height == 83);
	assert(it->second.width == 50);
}

/* Run the test. */
#define HARNESS GlyphPackerTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testMeasure)
ADD_TEST(testPack)
ADD_TEST(testLocations)
RUN_TESTS
