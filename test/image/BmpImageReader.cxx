/*
 * BmpImageReader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "BmpImageReader.hpp"

/** @brief Test for BmpImageReader. */
class BmpImageReaderTest {
public:
	void setUp();
	void testGetters();
	void testToArrayWithBadArray();
	void testToArrayWithBadSize();
	void testToArray();
private:
	BmpImageReader reader;
};

/** Read the image into memory. */
void BmpImageReaderTest::setUp() {
	
	reader.read("test/image/rgbw.bmp");
}

/** Ensures the file can be loaded. */
void BmpImageReaderTest::testGetters() {
	
	assert(reader.getWidth() == 2);
	assert(reader.getHeight() == 2);
	assert(reader.getFormat() == GL_BGR);
	assert(reader.getSize() == 16);
}

/** Ensures an exception is thrown. */
void BmpImageReaderTest::testToArrayWithBadArray() {
	
	char *array = NULL;
	
	try {
		reader.toArray(array, 0);
	} catch (ImageException &e) {
		return;
	}
	throw BasicException("Exception not caught properly!");
}

/** Ensures an exception is thrown. */
void BmpImageReaderTest::testToArrayWithBadSize() {
	
	char array[6];
	
	try {
		reader.toArray(array, 0);
	} catch (ImageException &e) {
		return;
	}
	throw BasicException("Exception not caught properly!");
}

/** Ensures pixel data is correct. */
void BmpImageReaderTest::testToArray() {
	
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
	
	BmpImageReaderTest test;
	
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
