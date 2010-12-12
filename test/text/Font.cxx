/*
 * Font.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Font.hpp"


/** @brief Test fixture for Font. */
class FontTest : public Test {
public:
	void testLessThanOperator();
};

/** Ensure Font can be compared correctly. */
void FontTest::testLessThanOperator() {
	
	vector<Font> v;
	set<Font> s;
	set<Font>::iterator it;
	
	v.push_back(Font("Arial", Font::PLAIN, 72));
	v.push_back(Font("Courier", Font::PLAIN, 32));
	v.push_back(Font("Courier", Font::PLAIN, 64));
	v.push_back(Font("Times", Font::BOLD, 72));
	
	s.insert(Font("Times", Font::BOLD, 72));
	s.insert(Font("Arial", Font::PLAIN, 72));
	s.insert(Font("Courier", Font::PLAIN, 64));
	s.insert(Font("Courier", Font::PLAIN, 32));
	
	for (it=s.begin(); it!=s.end(); ++it) {
		assert((*it) == v[distance(s.begin(),it)]);
	}
}

/* Run the test. */
#define HARNESS FontTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testLessThanOperator)
RUN_TESTS
