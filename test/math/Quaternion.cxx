/*
 * Quaternion.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Quaternion.hpp"

/** @brief Unit test for Quaternion. */
class QuaternionTest : public Test {
public:
	void testGetMatrix();
	void testMultiply();
private:
	Matrix mat;
	Quaternion quaA, quaB, quaC;
};

void QuaternionTest::testGetMatrix() {
	
	quaA.set(45, Vec4(0,1,0));
	quaA.print();
	mat = quaA.getMatrix();
	mat.print();
}

void QuaternionTest::testMultiply() {
	
	quaA.set(45, Vec4(0,1,0));
	quaB.set(30, Vec4(0,1,0));
	quaC = quaA * quaB;
	mat = quaC.getMatrix();
	mat.print();
}

/* Run the test. */
#define HARNESS QuaternionTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testGetMatrix)
ADD_TEST(testMultiply)
RUN_TESTS

