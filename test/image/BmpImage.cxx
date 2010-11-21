/*
 * BmpImage.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "BmpImage.hpp"

/** @brief Test for BmpImage. */
class BmpImageTest {
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

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	BmpImageTest test;
	
	cout << "BmpImageTest::testLoad()" << endl;
	test.testLoad();
	cout << "PASSED" << endl;
	cout << "PASSED ALL TESTS" << endl;
	return 0;
}
