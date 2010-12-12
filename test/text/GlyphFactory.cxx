/*
 * GlyphFactory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphFactory.hpp"


/** @brief Test fixture for GlyphFactory. */
class GlyphFactoryTest : public Test {
public:
	virtual void setUp();
	virtual void tearDown();
	void testGetInstance();
	void testCreate();
private:
	Font *font;
};

void GlyphFactoryTest::setUp() {
	
	font = new Font("Times", Font::BOLD, 72);
}

void GlyphFactoryTest::tearDown() {
	
	delete font;
}

/** Ensure get same instance back for same font. */
void GlyphFactoryTest::testGetInstance() {
	
	GlyphFactory *gf1, *gf2;
	
	gf1 = GlyphFactory::getInstance(*font);
	gf2 = GlyphFactory::getInstance(*font);
	
	assert(gf1 == gf2);
}

/** Ensure a glyph is created correctly. */
void GlyphFactoryTest::testCreate() {
	
	GlyphFactory *gf = GlyphFactory::getInstance(*font);
	Glyph *glyph = gf->create('A');
	
	cout << glyph->toString() << endl;
}

/* Run the test. */
#define HARNESS GlyphFactoryTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testGetInstance)
ADD_TEST(testCreate)
RUN_TESTS
