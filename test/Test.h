/*
 * Test.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_TEST_H
#define GLOOP_TEST_H

class Test {
public:
	virtual ~Test() {}
	virtual void setUp() {}
	virtual void tearDown() {}
};

#endif
