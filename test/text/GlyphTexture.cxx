/*
 * GlyphTexture.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "GlyphTexture.hpp"


/** Test fixture for GlyphTexture. */
class GlyphTextureTest : public Test {
public:
	virtual void setUp();
	void testFind();
private:
	GlyphTexture *glyphTexture;
	GlyphFactory *glyphFactory;
};

/** Initializes a test case. */
void GlyphTextureTest::setUp() {
	
	Font font("Arial", Font::PLAIN, 72);
	
	glyphFactory = GlyphFactory::getInstance(font);
	glyphTexture = GlyphTexture::getInstance(font);
}

/** Ensures a glyph can be found in the texture correctly. */
void GlyphTextureTest::testFind() {
	
	Glyph *glyph = glyphFactory->create('A');
	GlyphCoords gc = glyphTexture->find(glyph);
	
//	cout << "l " << gc.left << endl;
//	cout << "r " << gc.right << endl;
//	cout << "b " << gc.bottom << endl;
//	cout << "t " << gc.top << endl;
	
	assertEquals(gc.left, 0.909091);
	assertEquals(gc.right, 0.975936);
	assertEquals(gc.bottom, 0.666667);
	assertEquals(gc.top, 0.776439);
}

/* Run the test. */
#define HARNESS GlyphTextureTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testFind)
RUN_TESTS

