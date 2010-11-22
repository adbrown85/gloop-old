/*
 * Matrix.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include <ctime>
#include "Matrix.hpp"

/** @brief Unit test for Matrix. */
class MatrixTest : public Test {
public:
	void setUp();
	void testDeterminant();
	void testInverse();
	void testInverseTime();
	void testMultiplyTime();
	void testSetFromArray();
	void testTranspose();
	void testVectorMultiply();
	void testVectorMultiplyTime();
private:
	float TOLERANCE, ITERATIONS;
	Matrix m1, m2, m3;
};

void MatrixTest::setUp() {
	
	cout << "Setting up..." << endl;
	TOLERANCE = 0.000001;
	ITERATIONS = 100000;
	m1 = Matrix( 4.0, 3.0, 8.0, 7.0,
	             3.0, 2.0, 4.0, 6.0,
	             1.0, 6.0, 4.0, 5.0,
	             1.0, 2.0, 3.0, 4.0);
	m1.print();
}

void MatrixTest::testDeterminant() {
	
	float result;
	
	result = m1.getDeterminant();
	assert(result == 69);
}

void MatrixTest::testInverse() {
	
	m2 = m1.getInverse();
	m3 = m1 * m2;
	for (int i=0; i<4; ++i)
		assert(fabs(m3(i,i)-1.0) < TOLERANCE);
	for (int i=0; i<3; ++i) {
		for (int j=i+1; j<4; ++j)
			assert(fabs(m3(i,j)-0.0) < TOLERANCE);
	}
	for (int i=1; i<4; ++i) {
		for (int j=0; j<i; ++j)
			assert(fabs(m3(i,j)-0.0) < TOLERANCE);
	}
}

void MatrixTest::testInverseTime() {
	
	clock_t beg, end;
	
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1.getInverse();
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}

void MatrixTest::testMultiplyTime() {
	
	clock_t beg, end;
	
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1 * m2;
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}

void MatrixTest::testSetFromArray() {
	
	float arr[16] = { 1.0,  2.0,  3.0,  4.0,
	                  5.0,  6.0,  7.0,  8.0,
	                  9.0, 10.0, 11.0, 12.0,
	                 13.0, 14.0, 15.0, 16.0};
	
	m2.set(arr);
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			assert(arr[i*4+j] == m2(j,i));
		}
	}
}

void MatrixTest::testTranspose() {
	
	m3 = m1.getTranspose();
}

void MatrixTest::testVectorMultiply() {
	
	Vec4 v1(1.0, 1.0, 1.0, 1.0), v2;
	
	v2 = m2 * v1;
}

void MatrixTest::testVectorMultiplyTime() {
	
	clock_t beg, end;
	Vec4 v;
	
	beg = clock();
	for (int i=0; i<ITERATIONS; ++i)
		m1 * v;
	end = clock();
	cout << "  " << (end-beg) << " clocks." << endl;
	cout << "  " << ((double)end-beg) / CLOCKS_PER_SEC << " seconds." << endl;
}

#define HARNESS MatrixTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDeterminant)
ADD_TEST(testInverse)
ADD_TEST(testInverseTime)
ADD_TEST(testMultiplyTime)
ADD_TEST(testSetFromArray)
ADD_TEST(testTranspose)
ADD_TEST(testVectorMultiply)
ADD_TEST(testVectorMultiplyTime)
RUN_TESTS

