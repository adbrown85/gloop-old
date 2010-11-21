/*
 * BitmapImage.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "BitmapImage.hpp"

/** @brief Test for BitmapImage. */
class BitmapImageTest {
public:
	void testLoad();
};

/** Ensures the file can be loaded. */
void BitmapImageTest::testLoad() {
	
	BitmapImage *image;
	
	image = new BitmapImage("test/image/rgbw.bmp");
	assert(image->getAlignment() == 4);
	assert(image->getFormat() == GL_BGR);
	assert(image->getWidth() == 2);
	assert(image->getHeight() == 2);
	assert(image->getSize() == 16);
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	BitmapImageTest test;
	
	cout << "BitmapImageTest::testLoad()" << endl;
	test.testLoad();
	cout << "PASSED" << endl;
	cout << "PASSED ALL TESTS" << endl;
	return 0;
}
