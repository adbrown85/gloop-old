/*
 * BmpImageReader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "BmpImageReader.hpp"

/** @brief Test for BmpImageReader. */
class BmpImageReaderTest : public Test {
public:
	BmpImageReaderTest();
	void testGetters();
	void testToArrayWithBadArray();
	void testToArrayWithBadSize();
	void testToArray();
private:
	BmpImageReader reader;
};

/** Read the image into memory. */
BmpImageReaderTest::BmpImageReaderTest() {
	
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

/* Run the test. */
#define HARNESS BmpImageReaderTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testGetters)
ADD_TEST(testToArrayWithBadArray)
ADD_TEST(testToArrayWithBadSize)
ADD_TEST(testToArray)
RUN_TESTS

