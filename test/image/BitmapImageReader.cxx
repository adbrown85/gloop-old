/*
 * BitmapImageReader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "BitmapImageReader.hpp"

/** @brief Test for BitmapImageReader. */
class BitmapImageReaderTest {
public:
	void setUp();
	void testGetters();
	void testToArrayWithBadArray();
	void testToArrayWithBadSize();
	void testToArray();
private:
	BitmapImageReader reader;
};

/** Read the image into memory. */
void BitmapImageReaderTest::setUp() {
	
	reader.read("test/image/rgbw.bmp");
}

/** Ensures the file can be loaded. */
void BitmapImageReaderTest::testGetters() {
	
	assert(reader.getWidth() == 2);
	assert(reader.getHeight() == 2);
	assert(reader.getFormat() == GL_BGR);
	assert(reader.getSize() == 16);
}

/** Ensures an exception is thrown. */
void BitmapImageReaderTest::testToArrayWithBadArray() {
	
	char *array = NULL;
	
	try {
		reader.toArray(array, 0);
	} catch (ImageException &e) {
		return;
	}
	throw BasicException("Exception not caught properly!");
}

/** Ensures an exception is thrown. */
void BitmapImageReaderTest::testToArrayWithBadSize() {
	
	char array[6];
	
	try {
		reader.toArray(array, 0);
	} catch (ImageException &e) {
		return;
	}
	throw BasicException("Exception not caught properly!");
}

/** Ensures pixel data is correct. */
void BitmapImageReaderTest::testToArray() {
	
	unsigned char arr[16];
	
	reader.toArray((char*)arr, 16);
	
	// Bottom row (red and white)
	assert(arr[ 0] ==   0); // B
	assert(arr[ 1] ==   0); // G
	assert(arr[ 2] == 255); // R
	assert(arr[ 3] == 255); // B
	assert(arr[ 4] == 255); // G
	assert(arr[ 5] == 255); // R
	
	// Top row (blue and green)
	assert(arr[ 8] == 255); // B
	assert(arr[ 9] ==   0); // G
	assert(arr[10] ==   0); // R
	assert(arr[11] ==   0); // B
	assert(arr[12] == 255); // G
	assert(arr[13] ==   0); // R
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	BitmapImageReaderTest test;
	
	cout << "setUp()" << endl;
	test.setUp();
	cout << "testGetters()" << endl;
	test.testGetters();
	cout << "PASSED" << endl;
	cout << "testToArrayWithBadArray()" << endl;
	test.testToArrayWithBadArray();
	cout << "PASSED" << endl;
	cout << "testToArrayWithBadSize()" << endl;
	test.testToArrayWithBadSize();
	cout << "PASSED" << endl;
	cout << "testToArray()" << endl;
	test.testToArray();
	cout << "PASSED" << endl;
	cout << "PASSED ALL TESTS" << endl;
	return 0;
}
