/*
 * Vec4.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Vec4.hpp"

class Vec4Test {
public:
	void setUp();
	void tearDown();
	void testPrint();
	void testAddSubtract();
	void testMultiplyDivide();
	void testDoubleHalf();
private:
	Vec4 *A, *B;
};

void Vec4Test::setUp() {
	
	A = new Vec4(2, 2, 2);
	B = new Vec4(3, 4, 5);
}

void Vec4Test::tearDown() {
	
	delete A;
	delete B;
}

void Vec4Test::testPrint() {
	
	cout << "Printing vectors:" << endl;
	cout << " A: " << (*A) << endl;
	cout << " B: " << (*B) << endl;
}

void Vec4Test::testAddSubtract() {
	
	cout << "\nAdd/subtract of A, B:" << endl;
	cout << "  " <<  (*A) + (*B) << endl;
	cout << "  " <<  (*A) - (*B) << endl;
}

void Vec4Test::testMultiplyDivide() {
	
	cout << "\nMultiply/divide of A, B:" << endl;
	cout << "  " <<  (*A) * (*B) << endl;
	cout << "  " <<  (*A) / (*B) << endl;
}

void Vec4Test::testDoubleHalf() {
	
	cout << "\nDouble/half of A:" << endl;
	cout << "  " <<  (*A) * 2 << endl;
	cout << "  " <<  (*A) / 2 << endl;
}

int main(int argc, char *argv[]) {
	
	Vec4Test test;
	
	test.setUp();
	test.testPrint();
	test.testAddSubtract();
	test.testMultiplyDivide();
	test.testDoubleHalf();
	test.tearDown();
}

