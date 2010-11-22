/*
 * Configuration.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Configuration.hpp"

/** @brief Test for Configuration */
class ConfigurationTest : public Test {
public:
	void testGetMaxColorAttachments();
	void testGetMaxDrawBuffers();
};

void ConfigurationTest::testGetMaxColorAttachments() {
	
	cout << "MaxColorAttachments: ";
	cout << Configuration::getMaxColorAttachments << endl;
}

void ConfigurationTest::testGetMaxDrawBuffers() {
	
	cout << "MaxDrawBuffers: ";
	cout << Configuration::getMaxDrawBuffers << endl;
}

/* Run the test. */
#define HARNESS ConfigurationTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testGetMaxColorAttachments)
ADD_TEST(testGetMaxDrawBuffers)
RUN_TESTS

