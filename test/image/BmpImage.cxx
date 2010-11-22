/*
 * BmpImage.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "BmpImage.hpp"

/** @brief Test for BmpImage. */
class BmpImageTest : public Test {
public:
	void testLoad();
};

/** Ensures the file can be loaded. */
void BmpImageTest::testLoad() {
	
	BmpImage *image;
	
	image = new BmpImage("test/image/rgbw.bmp");
	assert(image->getAlignment() == 4);
	assert(image->getFormat() == GL_BGR);
	assert(image->getWidth() == 2);
	assert(image->getHeight() == 2);
	assert(image->getSize() == 16);
}

/* Run the test. */
#define HARNESS BmpImageTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testLoad)
RUN_TESTS
