/*
 * DatasetHeader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "DatasetHeader.hpp"
#define DATASETHEADERTEST_FILE "test/volume/bunny128.vlb"

/** @brief Unit test for DatasetHeader. */
class DatasetHeaderTest : public Test {
public:
	DatasetHeaderTest();
	virtual ~DatasetHeaderTest();
	void testConstructor();
private:
	DatasetHeader *header;
};

/** Creates the header. */
DatasetHeaderTest::DatasetHeaderTest() {
	header = new DatasetHeader(DATASETHEADERTEST_FILE);
}

/** Destroys the header. */
DatasetHeaderTest::~DatasetHeaderTest() {
	delete header;
}

/** Makes sure all the values were read correctly. */
void DatasetHeaderTest::testConstructor() {
	assert(header->getWidth() == 128);
	assert(header->getHeight() == 128);
	assert(header->getDepth() == 90);
	assert(header->getType() == "uint8");
	assert(header->getMin() == 0);
	assert(header->getMax() == 255);
	assert(header->getLow() == 0);
	assert(header->getHigh() == 255);
}

/* Run the test. */
#define HARNESS DatasetHeaderTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testConstructor)
RUN_TESTS

